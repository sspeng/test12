#include <libxml++/libxml++.h>
#include <fstream>
#include <stack>

#include "../../evaluate/commonTypes.h"



class TraceReader : public xmlpp::SaxParser
{
public:

  TraceReader(char* sampleFilename, char* timeFilename, char* attachedSampleFilename);
  virtual ~TraceReader();

 protected:

  enum { START, ID, STOP, OTHER } state;
  Marker currentMarker;
  // TODO: move to main module?
  std::ifstream timeFile, sampleFile;
  std::ofstream attachedSampleFile;
  std::stack<Marker> callstack;

  void handleMarker();

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
