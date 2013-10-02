#include "profileReader.h"

#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <math.h>


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
  if (name == "id") {
    state = ID;
  } else if (name == "hits") {
    state = HITS;
  } else if (name == "selfTime") {
    state = SELFTIME;
  } else if (name == "totalTime") {
    state = TOTALTIME;
  } else if (name == "selfEnergy") {
    state = SELFENERGY;
  } else if (name == "totalEnergy") {
    state = TOTALENERGY;
  } else {
    state = OTHER;
  }
}


void ProfileReader::on_end_element(const Glib::ustring& name)
{
  if (name == "totalEnergy") {
    double selfRatio = ((selfEnergy - selfTime) / hits);
    double totalRatio = ((totalEnergy - totalTime) / hits);
    if ( (fabs(selfRatio) > 1e-6) || (fabs(totalRatio) > 1e-6) )
    {
      std::cout << id << "   " << selfRatio << "   " << totalRatio << std::endl;
    }
    /*
    std::cout << "id=" << id << "   ";
    std::cout << "hits=" << hits << "   ";
    std::cout << "selfTime=" << selfTime << "   ";
    std::cout << "totalTime=" << totalTime << "   ";
    std::cout << "selfEnergy=" << selfEnergy << "   ";
    std::cout << "totalEnergy=" << totalEnergy << std::endl;
    */
  }
}


void ProfileReader::on_characters(const Glib::ustring& text)
{
  if (text != "\n") {
    if (state == ID) {
      sscanf(text.c_str(), "%p", &id);
    } else if (state == HITS) {
      sscanf(text.c_str(), "%u", &hits);
    } else if (state == SELFTIME) {
      if ( sscanf(text.c_str(), "%lf", &selfTime) == 1 ) {
	selfTime *= 1e-6;
      } else {
	exit(EXIT_FAILURE);
      }
    } else if (state == TOTALTIME) {
      if ( sscanf(text.c_str(), "%lf", &totalTime) == 1 ) {
	totalTime *= 1e-6;
      } else {
	exit(EXIT_FAILURE);
      }
    } else if (state == SELFENERGY) {
      sscanf(text.c_str(), "%lf", &selfEnergy);
    } else if (state == TOTALENERGY) {
      sscanf(text.c_str(), "%lf", &totalEnergy);
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
