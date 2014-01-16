#include "xmlOutput.h"

#include <stdlib.h>
#include <glibmm/markup.h>


XMLOutput::XMLOutput()
  : xmlpp::SaxParser()
{
  parseID = false;
}


XMLOutput::~XMLOutput()
{
  outfile.close();
}


void XMLOutput::merge(const char* inputFilename, std::map<routineID, Energies>* routines, const char* outputFilename) {
  this->routines = routines;
  outfile.open(outputFilename, std::ios::out | std::ios::trunc );
  this->parse_file(inputFilename);
}


void XMLOutput::on_start_document()
{
  outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>" << std::endl;
}


void XMLOutput::on_end_document()
{
  outfile << std::endl;
}

void XMLOutput::on_start_element(const Glib::ustring& name,
				     const AttributeList& attributes)
{
  outfile << "<" << name;
  for(xmlpp::SaxParser::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
    outfile << " " << iter->name << "=\"" << iter->value << "\"";
  }
  outfile << ">";

  if (name == "id") {
    parseID = true;
  } else {
    parseID = false;
  }
}


void XMLOutput::on_end_element(const Glib::ustring& name)
{
  outfile << "</" << name << ">";

  if (name == "totalTime") { // append energy values behind tag <totalTime>
    outfile << std::endl;
    outfile << "<selfEnergy>" << (*routines)[currentID].selfEnergy << "</selfEnergy>" << std::endl;
    outfile << "<totalEnergy>" << (*routines)[currentID].totalEnergy << "</totalEnergy>";
  }
}


void XMLOutput::on_characters(const Glib::ustring& text)
{
  if (parseID) {
    sscanf(text.c_str(), "%p", &currentID);
  }
  outfile << Glib::Markup::escape_text(text);
}


void XMLOutput::on_comment(const Glib::ustring& text)
{
  outfile << "<!--" << text << "-->" << std::endl;
}


void XMLOutput::on_warning(const Glib::ustring& text)
{
  outfile << "parser warning: " << text << std::endl;
}


void XMLOutput::on_error(const Glib::ustring& text)
{
  outfile << "parser error: " << text << std::endl;
  exit(EXIT_FAILURE);
}


void XMLOutput::on_fatal_error(const Glib::ustring& text)
{
  outfile << "parser fatal error: " << text << std::endl;
  exit(EXIT_FAILURE);
}
