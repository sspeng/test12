#include <libxml++/libxml++.h>
#include <fstream>

#include "commonTypes.h"


class ProfileMerger : public xmlpp::SaxParser
{
public:
  ProfileMerger();
  virtual ~ProfileMerger();
  void merge(const char* inputFilename, std::map<routineID, Energies>* routines, const char* outputFilename);

protected:
  std::map<routineID, Energies>* routines;
  std::ofstream outfile;

  bool parseID;
  void* currentID;

  //overrides:
  virtual void on_start_document();
  virtual void on_end_document();
  virtual void on_start_element(const Glib::ustring& name,
                                const AttributeList& properties);
  virtual void on_end_element(const Glib::ustring& name);
  virtual void on_characters(const Glib::ustring& characters);
  virtual void on_comment(const Glib::ustring& text);
  virtual void on_warning(const Glib::ustring& text);
  virtual void on_error(const Glib::ustring& text);
  virtual void on_fatal_error(const Glib::ustring& text);
};
