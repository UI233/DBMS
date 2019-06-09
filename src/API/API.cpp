#include "API.h"

API* API::api(nullptr);

BM::BufferManager& API::getBM() {
     if (!api)
        init();
    return api->buffer_manager;
}

void API::init() {
    if (!api)
        api = new API();
}
