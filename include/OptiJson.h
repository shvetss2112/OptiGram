#ifndef UNTITLED2_OPTIJSON_H
#define UNTITLED2_OPTIJSON_H
#include <cstddef>
#include "OptiString.h"
#include "OptiList.h"

struct JsonField {
    const char* key;
    OptiString<> val;
    const char* parent;
    JsonField(const JsonField& x)= default;
    JsonField():key(nullptr),parent(nullptr) {}
    JsonField(const char* key,const char* parent=nullptr):key(key),parent(parent) {}

    void registerValue(const char* nval) {
        this->val.append(nval);
    }

    void reciveNotification(const char* nkey,const char* nval,const char* nparent=nullptr) {
        if (!this->key) return;
        if (!nkey) return;
        if (!strcmp(this->key, nkey)) {
            this->registerValue(nval ? nval : "");
        }
    }

};

struct OptiJson {
    OptList<JsonField,10> fields;

    void parse(WiFiClientSecure& client) {
        bool token=false;
        bool kvflipflop=true;
        OptiString<20> tokenBuf;
        OptiString<20> keyToken;
        OptiString<20> valToken;
        while (client.connected() || client.available()) {
            if (client.available()) {
                char c = client.read();
                if (token&&c!='"')tokenBuf.append(c);
                if (c=='{')kvflipflop=true;
                if (c=='"') {
                    if (token) {
                        if (kvflipflop) {
                            keyToken=tokenBuf;
                        }
                        else {
                            valToken=tokenBuf;
                            notifyAll(keyToken.c_str(),valToken.c_str());
                        }
                        kvflipflop= !kvflipflop;
                        tokenBuf=OptiString<20>();
                    }
                    token=!token;
                }
            }
        }
    }
    const char* getItem(const char* key) {
        for (int i=0;i<fields.size;i++) {
            if (!strcmp(fields[i].key,key)) return fields[i].val.c_str();
        }
        return "\0";
    }
    void addFieldObserver(const char* key,const char* parent=nullptr) {
        fields.push(JsonField(key,parent));
    }
    void tabulateFields() {
        for (size_t i =0;i<fields.size;i++) {
        }
    }
    void notifyAll(const char* key,const char* val,const char* parent=nullptr) {
        for (size_t i =0;i<fields.size;i++) {
            fields[i].reciveNotification(key, val, parent);
        }
    }
};


#endif //UNTITLED2_OPTIJSON_H