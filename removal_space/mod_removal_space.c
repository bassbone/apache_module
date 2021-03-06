/* 
**  mod_removal_space.c -- Apache sample removal_space module
**  [Autogenerated via ``apxs -n removal_space -g'']
**
**  To play with this sample module first compile it into a
**  DSO file and install it into Apache's modules directory 
**  by running:
**
**    $ apxs -c -i mod_removal_space.c
**
**  Then activate it in Apache's httpd.conf file for instance
**  for the URL /removal_space in as follows:
**
**    #   httpd.conf
**    LoadModule removal_space_module modules/mod_removal_space.so
**    <Location /removal_space>
**    SetHandler removal_space
**    </Location>
**
**  Then after restarting Apache via
**
**    $ apachectl restart
**
**  you immediately can request the URL /removal_space and watch for the
**  output of this module. This can be achieved for instance via:
**
**    $ lynx -mime_header http://localhost/removal_space 
**
**  The output should be similar to the following one:
**
**    HTTP/1.1 200 OK
**    Date: Tue, 31 Mar 1998 14:42:22 GMT
**    Server: Apache/1.3.4 (Unix)
**    Connection: close
**    Content-Type: text/html
**  
**    The sample page from mod_removal_space.c
*/ 

#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"
#include "apr_strings.h"
#include "apr_general.h"
#include "util_filter.h"
#include "apr_buckets.h"
#include "http_request.h"

#define PUT(f, bb, s) APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_immortal_create(s, strlen(s), f->c->bucket_alloc))

static apr_status_t removal_space_out_filter(ap_filter_t *f, apr_bucket_brigade *in_bb) {

    apr_status_t err;
    apr_size_t buf_len = 0;
    unsigned char* ptr;
    unsigned char* buf = 0;

    err = apr_brigade_pflatten(in_bb, (char**)&buf, &buf_len, f->r->pool);
    if (err) return err;
    apr_brigade_cleanup(in_bb);

    PUT(f, in_bb, "test");

    //PUT(f, in_bb, ptr);

    APR_BRIGADE_INSERT_TAIL(in_bb, apr_bucket_eos_create(f->c->bucket_alloc));

    ap_remove_output_filter(f);

    return ap_pass_brigade(f->next, in_bb);
}

static void removal_space_register_hooks(apr_pool_t *p)
{
    ap_register_output_filter("removal_space", removal_space_out_filter, NULL, AP_FTYPE_RESOURCE);
}

/* Dispatch list for API hooks */
module AP_MODULE_DECLARE_DATA removal_space_module = {
    STANDARD20_MODULE_STUFF, 
    NULL,                  /* create per-dir    config structures */
    NULL,                  /* merge  per-dir    config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    removal_space_register_hooks  /* register hooks                      */
};

