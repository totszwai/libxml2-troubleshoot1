#include <libxml/c14n.h>
#include <libxml/xmlschemas.h>


// For xmlSubstituteEntitiesDefault deprecation:
//  xmlSubstituteEntitiesDefault(1) > XML_PARSE_NOENT
// For xmlLoadExtDtdDefaultValue deprecation:
//  XML_DETECT_IDS > XML_PARSE_DTDLOAD
//  XML_COMPLETE_ATTRS > XML_PARSE_DTDATTR 
#define XMLMGR_PARSER_OPTIONS               (XML_PARSE_RECOVER | XML_PARSE_NOENT | XML_PARSE_DTDLOAD | XML_PARSE_DTDATTR | XML_PARSE_NOBLANKS | XML_PARSE_HUGE)

const char* dump(xmlDocPtr doc, bool pretty = true)
{
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlBufferPtr buf = xmlBufferCreate();
    if (buf == NULL) {
        fprintf(stderr, "dump: failed to create buffer\n");
        return NULL;
    }

    xmlNodeDump(buf, doc, root, 0, pretty ? 1 : 0);
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

    const char* sample = "<root xmlns:ds='http://www.w3.org/2000/09/xmldsig#'></root>";
    if (load(doc, sample))
    {
        fprintf(stdout, "%s\n", dump(doc));

        bool ok = false;
        xmlNodePtr newNode = nullptr;

        ok = xmlParseBalancedChunkMemory(doc, NULL, NULL, 0,
                                         BAD_CAST "<X509Certificate>MII...SigningCertificate</X509Certificate>",
                                         &newNode) == 0;
        if (ok)
            fprintf(stdout, "XML string is valid\n");

        ok = xmlParseBalancedChunkMemory(doc, NULL, NULL, 0,
                                         BAD_CAST "<ds:X509Certificate>MII...SigningCertificate</ds:X509Certificate>",
                                         &newNode) == 0;

        if (!ok)
            fprintf(stdout, "Namespace is the root cause but how to fix it?\n");

        xmlFreeDoc(doc);
    }

    return 0;
}