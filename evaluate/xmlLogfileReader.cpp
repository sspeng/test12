#include "xmlLogfileReader.h"

#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <iomanip> // TODO: remove


XMLLogfileReader::XMLLogfileReader()
  : xmlpp::SaxParser()
{
}


XMLLogfileReader::~XMLLogfileReader()
{
}


void XMLLogfileReader::registerNewMarkerCallback(void (*handler)(Marker newMarker)) {
  handleNewMarker = handler;
}


void XMLLogfileReader::on_start_document()
{
}


void XMLLogfileReader::on_end_document()
{
}

void XMLLogfileReader::on_start_element(const Glib::ustring& name,
				     const AttributeList& attributes)
{
  if (name == "call")
    {
      state = CALL;
    }
  else if (name == "start")
    {
      state = START;
      currentMarker.isStartMarker = true;
    }
  else if (name == "id")
    {
      state = ID;
    }
  else if (name == "stop")
    {
      state = STOP;
      currentMarker.isStartMarker = false;
      currentMarker.routine = NULL;
    }
  else
    {
      state = OTHER;
    }
}


void XMLLogfileReader::on_end_element(const Glib::ustring& name)
{
  if (name == "call")
    {
    }
  else if (name == "start")
    {
    }
  else if (name == "id")
    {
      handleNewMarker(currentMarker); // we didn't had the full information before!
    }
  else if (name == "stop")
    {
      handleNewMarker(currentMarker);
    }
  else // remaining tags
    {
    }
}


void XMLLogfileReader::on_characters(const Glib::ustring& text)
{
  if (state == CALL)
    {
    }
  else if (state == START)
    {
      //sscanf(text.c_str(), "%lu.%lu", &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec); // OLD VERSION
      long usecs;
      sscanf(text.c_str(), "%lu", &usecs);
      currentMarker.time.tv_sec  = (usecs / 1000000);
      currentMarker.time.tv_nsec = (usecs % 1000000) * 1000;
      //std::cerr << "read: " << currentMarker.time.tv_sec << "." << std::setfill('0') << std::setw(9) << currentMarker.time.tv_nsec << std::endl;
    }
  else if (state == ID)
    {
      sscanf(text.c_str(), "%p", &currentMarker.routine);
      std::cout << "routineID: " << currentMarker.routine << std::endl;
    }
  else if (state == STOP)
    {
      //sscanf(text.c_str(), "%lu.%lu", &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec); // OLD VERSION
      long usecs;
      sscanf(text.c_str(), "%lu", &usecs);
      currentMarker.time.tv_sec  = (usecs / 1000000);
      currentMarker.time.tv_nsec = (usecs % 1000000) * 1000;
      //std::cerr << "read: " << currentMarker.time.tv_sec << "." << std::setfill('0') << std::setw(9) << currentMarker.time.tv_nsec << std::endl;
    }
  else // remaining tags
    {
    }
}


void XMLLogfileReader::on_comment(const Glib::ustring& text)
{
}


void XMLLogfileReader::on_warning(const Glib::ustring& text)
{
  std::cout << "parser warning: " << text << std::endl;
}


void XMLLogfileReader::on_error(const Glib::ustring& text)
{
  std::cout << "parser error: " << text << std::endl;
  exit(EXIT_FAILURE);
}


void XMLLogfileReader::on_fatal_error(const Glib::ustring& text)
{
  std::cout << "parser fatal error: " << text << std::endl;
  exit(EXIT_FAILURE);
}
