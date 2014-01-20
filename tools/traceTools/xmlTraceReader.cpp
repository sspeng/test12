#include "xmlTraceReader.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>



void XMLTraceReader::registerNewMarkerCallback(void (*handler)(Marker newMarker)) {
  handleNewMarker = handler;
}


XMLTraceReader::XMLTraceReader()
  : xmlpp::SaxParser()
{
}


XMLTraceReader::~XMLTraceReader()
{
}


void XMLTraceReader::on_start_document()
{
}


void XMLTraceReader::on_end_document()
{
}

void XMLTraceReader::on_start_element(const Glib::ustring& name,
				     const AttributeList& attributes)
{
  if (name == "start")
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


void XMLTraceReader::on_end_element(const Glib::ustring& name)
{
  if (name == "start")
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


void XMLTraceReader::on_characters(const Glib::ustring& text)
{
  if (state == START)
    {
      sscanf(text.c_str(), "%lu.%lu", &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec);
    }
  else if (state == ID)
    {
      sscanf(text.c_str(), "%p", &currentMarker.routine);
    }
  else if (state == STOP)
    {
      sscanf(text.c_str(), "%lu.%lu", &currentMarker.time.tv_sec, &currentMarker.time.tv_nsec);
    }
  else // remaining tags
    {
    }
}


void XMLTraceReader::on_comment(const Glib::ustring& text)
{
}


void XMLTraceReader::on_warning(const Glib::ustring& text)
{
  std::cout << "parser warning: " << text << std::endl;
}


void XMLTraceReader::on_error(const Glib::ustring& text)
{
  std::cout << "parser error: " << text << std::endl;
  exit(EXIT_FAILURE);
}


void XMLTraceReader::on_fatal_error(const Glib::ustring& text)
{
  std::cout << "parser fatal error: " << text << std::endl;
  exit(EXIT_FAILURE);
}
