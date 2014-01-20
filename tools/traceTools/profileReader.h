// TODO: reuse ../../evaluate/xmlOutput.* instead?

#include <libxml++/libxml++.h>


class ProfileReader : public xmlpp::SaxParser
{
public:

  ProfileReader();
  virtual ~ProfileReader();

  void registerNewEntryCallback(void (*handler)(const Glib::ustring& name, void* id));

protected:

  enum { NAME, ID, OTHER } state;

  Glib::ustring routineName;
  void* routineId;

  void (*handleNewEntry)(const Glib::ustring& name, void* id);

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
