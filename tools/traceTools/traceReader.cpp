#include "traceReader.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>



void TraceReader::registerNewMarkerCallback(void (*handler)(Marker newMarker)) {
  handleNewMarker = handler;
}


TraceReader::TraceReader()
  : xmlpp::SaxParser()
{
}


TraceReader::~TraceReader()
{
}


void TraceReader::on_start_document()
{
}


void TraceReader::on_end_document()
{
}

void TraceReader::on_start_element(const Glib::ustring& name,
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


void TraceReader::on_end_element(const Glib::ustring& name)
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


void TraceReader::on_characters(const Glib::ustring& text)
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


void TraceReader::on_comment(const Glib::ustring& text)
{
}


void TraceReader::on_warning(const Glib::ustring& text)
{
  std::cout << "parser warning: " << text << std::endl;
}


void TraceReader::on_error(const Glib::ustring& text)
{
  std::cout << "parser error: " << text << std::endl;
  exit(EXIT_FAILURE);
}


void TraceReader::on_fatal_error(const Glib::ustring& text)
{
  std::cout << "parser fatal error: " << text << std::endl;
  exit(EXIT_FAILURE);
}
