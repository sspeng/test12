#include <libxml++/libxml++.h>


class ProfileReader : public xmlpp::SaxParser
{
public:

  ProfileReader();
  virtual ~ProfileReader();

 protected:

  enum {ID, HITS, SELFTIME, TOTALTIME, SELFENERGY, TOTALENERGY, OTHER} state;

  void* id;
  unsigned hits;
  double tmp;
  double selfTime, totalTime, selfEnergy, totalEnergy;

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
