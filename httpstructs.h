typedef struct _HTTP_RESPONSE
{
    char *protocol;
    char *httpCode;
    char *contentType;
    int contentLength;
    char *body;
}HTTP_RESPONSE;