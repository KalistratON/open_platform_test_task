#ifndef _MACRO_HEADER
#define _MACRO_HEADER

#ifndef _EXPORT
#ifdef _WIN32
#define _EXPORT __declspec(dllexport)
#else 
#define _EXPORT 
#endif
#endif

#define _DEFINE_PROPERTY(PTYPE,PNAME) \
    \
    public: \
        _EXPORT const PTYPE & PNAME() const { return my ## PNAME ; } \
        _EXPORT PTYPE & PNAME() { return my ## PNAME ; } \
    private: \
        PTYPE   my ## PNAME; \
    public:

#endif