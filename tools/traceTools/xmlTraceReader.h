// TODO: reuse ../../evaluate/xmlLogfileReader.* instead?

#include <libxml++/libxml++.h>

#include "../../evaluate/commonTypes.h"



class XMLTraceReader : public xmlpp::SaxParser
{
public:

  XMLTraceReader();
  virtual ~XMLTraceReader();

  void registerNewMarkerCallback(void (*handler)(Marker marker));

 protected:

  bool withinLogSection;

  enum { START, ID, STOP, OTHER } state;
  Marker currentMarker;

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
