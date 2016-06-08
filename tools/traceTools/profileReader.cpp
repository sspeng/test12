/* TODO: a SAX parser may return strings in between tags as multiple chunks ~> concatenate chunks */

#include "profileReader.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>



void ProfileReader::registerNewEntryCallback(void (*handler)(const Glib::ustring& name, void* id)) {
  handleNewEntry = handler;
}


ProfileReader::ProfileReader()
  : xmlpp::SaxParser()
{
}


ProfileReader::~ProfileReader()
{
}


void ProfileReader::on_start_document()
{
}


void ProfileReader::on_end_document()
{
}

void ProfileReader::on_start_element(const Glib::ustring& name,
				     const AttributeList& attributes)
{
  if (withinCoreSection)
    {
      if (name == "name")
	{
	  state = NAME;
	}
      else if (name == "id")
	{
	  state = ID;
	}
      else
	{
	  state = OTHER;
	}
    }

  if (name == "core") withinCoreSection = true;
}


void ProfileReader::on_end_element(const Glib::ustring& name)
{
  if (name == "core") withinCoreSection = false;

  if (withinCoreSection) {
    if (name == "name")
      {
      }
    else if (name == "id")
      {
	handleNewEntry(routineName, routineId);
      }
    else // remaining tags
      {
      }
  }
}


void ProfileReader::on_characters(const Glib::ustring& text)
{
  if (withinCoreSection)
    {
      if (state == NAME)
	{
	  if (text != "\n")
	    routineName = text;
	}
      else if (state == ID)
	{
	  sscanf(text.c_str(), "%p", &routineId);
	}
      else // remaining tags
	{
	}
    }
}


void ProfileReader::on_comment(const Glib::ustring& text)
{
}


void ProfileReader::on_warning(const Glib::ustring& text)
{
  std::cout << "parser warning: " << text << std::endl;
}


void ProfileReader::on_error(const Glib::ustring& text)
{
  std::cout << "parser error: " << text << std::endl;
  exit(EXIT_FAILURE);
}


void ProfileReader::on_fatal_error(const Glib::ustring& text)
{
  std::cout << "parser fatal error: " << text << std::endl;
  exit(EXIT_FAILURE);
}
