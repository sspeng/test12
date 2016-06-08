#include <libxml++/libxml++.h>

#include "commonTypes.h"


class XMLLogfileReader : public xmlpp::SaxParser
{
public:
  bool withinLogBlock;
  enum { START, ID, STOP, OTHER } state;
  Marker currentMarker;

  XMLLogfileReader();
  virtual ~XMLLogfileReader();
  void registerNewMarkerCallback(void (*handler)(Marker marker));

 protected:
  void (*handleNewMarker)(Marker marker);

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
