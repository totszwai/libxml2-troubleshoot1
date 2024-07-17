
#include <xmlsec/xmlsec.h>
#include <xmlsec/xmldsig.h>
#include <xmlsec/errors.h>

#include <libxml/c14n.h>
#include <libxml/xmlschemas.h>


// For xmlSubstituteEntitiesDefault deprecation:
//  xmlSubstituteEntitiesDefault(1) > XML_PARSE_NOENT
// For xmlLoadExtDtdDefaultValue deprecation:
//  XML_DETECT_IDS > XML_PARSE_DTDLOAD
//  XML_COMPLETE_ATTRS > XML_PARSE_DTDATTR 
#define XMLMGR_PARSER_OPTIONS               (XML_PARSE_RECOVER | XML_PARSE_NOENT | XML_PARSE_DTDLOAD | XML_PARSE_DTDATTR | XML_PARSE_NOBLANKS | XML_PARSE_HUGE)

const char* dump(xmlDocPtr doc, bool format = true)
{
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlBufferPtr buf = xmlBufferCreate();
    if (buf == NULL) {
        fprintf(stderr, "dump: failed to create buffer\n");
        return NULL;
    }

    xmlNodeDump(buf, doc, root, 0, format ? 1 : 0);
    return buf->use > 0 ? (const char*) buf->content : NULL;
}

bool load(xmlDocPtr &doc, const char* xml) {
    doc = xmlReadDoc((const xmlChar *) xml, NULL, NULL, XMLMGR_PARSER_OPTIONS);
    return doc != NULL;
}

int main(int argc, char **argp)
{
    xmlInitParser();
    LIBXML_TEST_VERSION


    xmlDocPtr doc = NULL;

    const char* expected = "<root><a>test</a></root>";
    if (load(doc, expected)) 
    {
        fprintf(stdout, "%s\n", dump(doc));
        xmlFreeDoc(doc);
    }

    const char* unexpected = "<root>"
                             "  <a>"
                             "    test"
                             "  </a>"
                             "</root>";
    if (load(doc, unexpected))
    {
        fprintf(stdout, "%s\n", dump(doc));
        xmlFreeDoc(doc);
    }

    return 0;
}