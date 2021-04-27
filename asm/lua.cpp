#include "fp_call.h"
#include <lua.hpp>
#include <windows.h>
using namespace base;

uintptr_t empty_func()
{
	return 0;
}
uintptr_t get_proaddress(const char* name)
{
	HMODULE handle = GetModuleHandleA("luacore.dll");
	if (!handle) handle = LoadLibraryA("luacore.dll");
	if (!handle) handle = GetModuleHandleA("lua53.dll");
	if (!handle) handle = LoadLibraryA("lua53.dll");
	if (!handle) handle = GetModuleHandleA(nullptr);
	if (handle != 0)
		return (uintptr_t)GetProcAddress(handle, name);
	return (uintptr_t)&empty_func;
}

lua_State * lua_newstate(lua_Alloc f, void* ud) {
	return ((decltype(lua_newstate)*)get_proaddress("lua_newstate"))(f, ud);
}
lua_State* lua_newstate2(lua_Alloc f, void* ud, unsigned int seed) {
	return ((decltype(lua_newstate2)*)get_proaddress("lua_newstate2"))(f, ud, seed);
}
void       lua_setgchash(lua_State* L, int idx) {
	((decltype(lua_setgchash)*)get_proaddress("lua_setgchash"))(L, idx);
}
void       lua_close(lua_State* L) {
	((decltype(lua_close)*)get_proaddress("lua_close"))(L);
}
lua_State* lua_newthread(lua_State* L) {
	return ((decltype(lua_newthread)*)get_proaddress("lua_newthread"))(L);
}
lua_CFunction lua_atpanic(lua_State* L, lua_CFunction panicf) {
	return ((decltype(lua_atpanic)*)get_proaddress("lua_atpanic"))(L, panicf);
}
const lua_Number* lua_version(lua_State* L) {
	return ((decltype(lua_version)*)get_proaddress("lua_version"))(L);
}
int   lua_absindex(lua_State* L, int idx) {
	return ((decltype(lua_absindex)*)get_proaddress("lua_absindex"))(L, idx);
}
int   lua_gettop(lua_State* L) {
	return ((decltype(lua_gettop)*)get_proaddress("lua_gettop"))(L);
}
void  lua_settop(lua_State* L, int idx) {
	((decltype(lua_settop)*)get_proaddress("lua_settop"))(L, idx);
}
void  lua_pushvalue(lua_State* L, int idx) {
	((decltype(lua_pushvalue)*)get_proaddress("lua_pushvalue"))(L, idx);
}
void  lua_rotate(lua_State* L, int idx, int n) {
	((decltype(lua_rotate)*)get_proaddress("lua_rotate"))(L, idx, n);
}
void  lua_copy(lua_State* L, int fromidx, int toidx) {
	((decltype(lua_copy)*)get_proaddress("lua_copy"))(L, fromidx, toidx);
}
int   lua_checkstack(lua_State* L, int n) {
	return ((decltype(lua_checkstack)*)get_proaddress("lua_checkstack"))(L, n);
}
void  lua_xmove(lua_State* from, lua_State* to, int n) {
	((decltype(lua_xmove)*)get_proaddress("lua_xmove"))(from, to, n);
}
int             lua_isnumber(lua_State* L, int idx) {
	return ((decltype(lua_isnumber)*)get_proaddress("lua_isnumber"))(L, idx);
}
int             lua_isstring(lua_State* L, int idx) {
	return ((decltype(lua_isstring)*)get_proaddress("lua_isstring"))(L, idx);
}
int             lua_iscfunction(lua_State* L, int idx) {
	return ((decltype(lua_iscfunction)*)get_proaddress("lua_iscfunction"))(L, idx);
}
int             lua_isinteger(lua_State* L, int idx) {
	return ((decltype(lua_isinteger)*)get_proaddress("lua_isinteger"))(L, idx);
}
int             lua_isuserdata(lua_State* L, int idx) {
	return ((decltype(lua_isuserdata)*)get_proaddress("lua_isuserdata"))(L, idx);
}
int             lua_type(lua_State* L, int idx) {
	return ((decltype(lua_type)*)get_proaddress("lua_type"))(L, idx);
}
const char* lua_typename(lua_State* L, int tp) {
	return ((decltype(lua_typename)*)get_proaddress("lua_typename"))(L, tp);
}
lua_Number      lua_tonumberx(lua_State* L, int idx, int* isnum) {
	return ((decltype(lua_tonumberx)*)get_proaddress("lua_tonumberx"))(L, idx, isnum);
}
lua_Integer     lua_tointegerx(lua_State* L, int idx, int* isnum) {
	return ((decltype(lua_tointegerx)*)get_proaddress("lua_tointegerx"))(L, idx, isnum);
}
int             lua_toboolean(lua_State* L, int idx) {
	return ((decltype(lua_toboolean)*)get_proaddress("lua_toboolean"))(L, idx);
}
const char* lua_tolstring(lua_State* L, int idx, size_t* len) {
	return ((decltype(lua_tolstring)*)get_proaddress("lua_tolstring"))(L, idx, len);
}
size_t          lua_rawlen(lua_State* L, int idx) {
	return ((decltype(lua_rawlen)*)get_proaddress("lua_rawlen"))(L, idx);
}
lua_CFunction   lua_tocfunction(lua_State* L, int idx) {
	return ((decltype(lua_tocfunction)*)get_proaddress("lua_tocfunction"))(L, idx);
}
void* lua_touserdata(lua_State* L, int idx) {
	return ((decltype(lua_touserdata)*)get_proaddress("lua_touserdata"))(L, idx);
}
lua_State* lua_tothread(lua_State* L, int idx) {
	return ((decltype(lua_tothread)*)get_proaddress("lua_tothread"))(L, idx);
}
const void* lua_topointer(lua_State* L, int idx) {
	return ((decltype(lua_topointer)*)get_proaddress("lua_topointer"))(L, idx);
}
void  lua_arith(lua_State* L, int op) {
	((decltype(lua_arith)*)get_proaddress("lua_arith"))(L, op);
}
int   lua_rawequal(lua_State* L, int idx1, int idx2) {
	return ((decltype(lua_rawequal)*)get_proaddress("lua_rawequal"))(L, idx1, idx2);
}
int   lua_compare(lua_State* L, int idx1, int idx2, int op) {
	return ((decltype(lua_compare)*)get_proaddress("lua_compare"))(L, idx1, idx2, op);
}
void        lua_pushnil(lua_State* L) {
	((decltype(lua_pushnil)*)get_proaddress("lua_pushnil"))(L);
}
void        lua_pushnumber(lua_State* L, lua_Number n) {
	((decltype(lua_pushnumber)*)get_proaddress("lua_pushnumber"))(L, n);
}
void        lua_pushinteger(lua_State* L, lua_Integer n) {
	((decltype(lua_pushinteger)*)get_proaddress("lua_pushinteger"))(L, n);
}
const char* lua_pushlstring(lua_State* L, const char* s, size_t len) {
	return ((decltype(lua_pushlstring)*)get_proaddress("lua_pushlstring"))(L, s, len);
}
const char* lua_pushstring(lua_State* L, const char* s) {
	return ((decltype(lua_pushstring)*)get_proaddress("lua_pushstring"))(L, s);
}
const char* lua_pushvfstring(lua_State* L, const char* fmt,
	va_list argp) {
	return ((decltype(lua_pushvfstring)*)get_proaddress("lua_pushvfstring"))(L, fmt, argp);
}
const char* lua_pushfstring(lua_State* L, const char* fmt, ...) {
	return ((decltype(lua_pushfstring)*)get_proaddress("lua_pushfstring"))(L, fmt);
}
void  lua_pushcclosure(lua_State* L, lua_CFunction fn, int n) {
	((decltype(lua_pushcclosure)*)get_proaddress("lua_pushcclosure"))(L, fn, n);
}
void  lua_pushboolean(lua_State* L, int b) {
	((decltype(lua_pushboolean)*)get_proaddress("lua_pushboolean"))(L, b);
}
void  lua_pushlightuserdata(lua_State* L, void* p) {
	((decltype(lua_pushlightuserdata)*)get_proaddress("lua_pushlightuserdata"))(L, p);
}
int   lua_pushthread(lua_State* L) {
	return ((decltype(lua_pushthread)*)get_proaddress("lua_pushthread"))(L);
}
int lua_getglobal(lua_State* L, const char* name) {
	return ((decltype(lua_getglobal)*)get_proaddress("lua_getglobal"))(L, name);
}
int lua_gettable(lua_State* L, int idx) {
	return ((decltype(lua_gettable)*)get_proaddress("lua_gettable"))(L, idx);
}
int lua_getfield(lua_State* L, int idx, const char* k) {
	return ((decltype(lua_getfield)*)get_proaddress("lua_getfield"))(L, idx, k);
}
int lua_geti(lua_State* L, int idx, lua_Integer n) {
	return ((decltype(lua_geti)*)get_proaddress("lua_geti"))(L, idx, n);
}
int lua_rawget(lua_State* L, int idx) {
	return ((decltype(lua_rawget)*)get_proaddress("lua_rawget"))(L, idx);
}
int lua_rawgeti(lua_State* L, int idx, lua_Integer n) {
	return ((decltype(lua_rawgeti)*)get_proaddress("lua_rawgeti"))(L, idx, n);
}
int lua_rawgetp(lua_State* L, int idx, const void* p) {
	return ((decltype(lua_rawgetp)*)get_proaddress("lua_rawgetp"))(L, idx, p);
}
void  lua_createtable(lua_State* L, int narr, int nrec) {
	((decltype(lua_createtable)*)get_proaddress("lua_createtable"))(L, narr, nrec);
}
void* lua_newuserdata(lua_State* L, size_t sz) {
	return ((decltype(lua_newuserdata)*)get_proaddress("lua_newuserdata"))(L, sz);
}
int   lua_getmetatable(lua_State* L, int objindex) {
	return ((decltype(lua_getmetatable)*)get_proaddress("lua_getmetatable"))(L, objindex);
}
int  lua_getuservalue(lua_State* L, int idx) {
	return ((decltype(lua_getuservalue)*)get_proaddress("lua_getuservalue"))(L, idx);
}
void  lua_setglobal(lua_State* L, const char* name) {
	((decltype(lua_setglobal)*)get_proaddress("lua_setglobal"))(L, name);
}
void  lua_settable(lua_State* L, int idx) {
	((decltype(lua_settable)*)get_proaddress("lua_settable"))(L, idx);
}
void  lua_setfield(lua_State* L, int idx, const char* k) {
	((decltype(lua_setfield)*)get_proaddress("lua_setfield"))(L, idx, k);
}
void  lua_seti(lua_State* L, int idx, lua_Integer n) {
	((decltype(lua_seti)*)get_proaddress("lua_seti"))(L, idx, n);
}
void  lua_rawset(lua_State* L, int idx) {
	((decltype(lua_rawset)*)get_proaddress("lua_rawset"))(L, idx);
}
void  lua_rawseti(lua_State* L, int idx, lua_Integer n) {
	((decltype(lua_rawseti)*)get_proaddress("lua_rawseti"))(L, idx, n);
}
void  lua_rawsetp(lua_State* L, int idx, const void* p) {
	((decltype(lua_rawsetp)*)get_proaddress("lua_rawsetp"))(L, idx, p);
}
int   lua_setmetatable(lua_State* L, int objindex) {
	return ((decltype(lua_setmetatable)*)get_proaddress("lua_setmetatable"))(L, objindex);
}
void  lua_setuservalue(lua_State* L, int idx) {
	((decltype(lua_setuservalue)*)get_proaddress("lua_setuservalue"))(L, idx);
}
void  lua_callk(lua_State* L, int nargs, int nresults,
	lua_KContext ctx, lua_KFunction k) {
	((decltype(lua_callk)*)get_proaddress("lua_callk"))(L, nargs, nresults, ctx, k);
}
int   lua_pcallk(lua_State* L, int nargs, int nresults, int errfunc,
	lua_KContext ctx, lua_KFunction k) {
	return ((decltype(lua_pcallk)*)get_proaddress("lua_pcallk"))(L, nargs, nresults, errfunc, ctx, k);
}
int   lua_load(lua_State* L, lua_Reader reader, void* dt,
	const char* chunkname, const char* mode) {
	return ((decltype(lua_load)*)get_proaddress("lua_load"))(L, reader, dt, chunkname, mode);
}
int lua_dump(lua_State* L, lua_Writer writer, void* data, int strip) {
	return ((decltype(lua_dump)*)get_proaddress("lua_dump"))(L, writer, data, strip);
}
int  lua_yieldk(lua_State* L, int nresults, lua_KContext ctx,
	lua_KFunction k) {
	return ((decltype(lua_yieldk)*)get_proaddress("lua_yieldk"))(L, nresults, ctx, k);
}
int  lua_resume(lua_State* L, lua_State* from, int narg) {
	return ((decltype(lua_resume)*)get_proaddress("lua_resume"))(L, from, narg);
}
int  lua_status(lua_State* L) {
	return ((decltype(lua_status)*)get_proaddress("lua_status"))(L);
}
int lua_isyieldable(lua_State* L) {
	return ((decltype(lua_isyieldable)*)get_proaddress("lua_isyieldable"))(L);
}
int lua_gc(lua_State* L, int what, int data) {
	return ((decltype(lua_gc)*)get_proaddress("lua_gc"))(L, what, data);
}
int   lua_error(lua_State* L) {
	return ((decltype(lua_error)*)get_proaddress("lua_error"))(L);
}
int   lua_next(lua_State* L, int idx) {
	return ((decltype(lua_next)*)get_proaddress("lua_next"))(L, idx);
}
void  lua_concat(lua_State* L, int n) {
	((decltype(lua_concat)*)get_proaddress("lua_concat"))(L, n);
}
void  lua_len(lua_State* L, int idx) {
	((decltype(lua_len)*)get_proaddress("lua_len"))(L, idx);
}
size_t   lua_stringtonumber(lua_State* L, const char* s) {
	return ((decltype(lua_stringtonumber)*)get_proaddress("lua_stringtonumber"))(L, s);
}
lua_Alloc lua_getallocf(lua_State* L, void** ud) {
	return ((decltype(lua_getallocf)*)get_proaddress("lua_getallocf"))(L, ud);
}
void      lua_setallocf(lua_State* L, lua_Alloc f, void* ud) {
	((decltype(lua_setallocf)*)get_proaddress("lua_setallocf"))(L, f, ud);
}
int lua_getstack(lua_State* L, int level, lua_Debug* ar) {
	return ((decltype(lua_getstack)*)get_proaddress("lua_getstack"))(L, level, ar);
}
int lua_getinfo(lua_State* L, const char* what, lua_Debug* ar) {
	return ((decltype(lua_getinfo)*)get_proaddress("lua_getinfo"))(L, what, ar);
}
const char* lua_getlocal(lua_State* L, const lua_Debug* ar, int n) {
	return ((decltype(lua_getlocal)*)get_proaddress("lua_getlocal"))(L, ar, n);
}
const char* lua_setlocal(lua_State* L, const lua_Debug* ar, int n) {
	return ((decltype(lua_setlocal)*)get_proaddress("lua_setlocal"))(L, ar, n);
}
const char* lua_getupvalue(lua_State* L, int funcindex, int n) {
	return ((decltype(lua_getupvalue)*)get_proaddress("lua_getupvalue"))(L, funcindex, n);
}
const char* lua_setupvalue(lua_State* L, int funcindex, int n) {
	return ((decltype(lua_setupvalue)*)get_proaddress("lua_setupvalue"))(L, funcindex, n);
}
void* lua_upvalueid(lua_State* L, int fidx, int n) {
	return ((decltype(lua_upvalueid)*)get_proaddress("lua_upvalueid"))(L, fidx, n);
}
void  lua_upvaluejoin(lua_State* L, int fidx1, int n1,
	int fidx2, int n2) {
	((decltype(lua_upvaluejoin)*)get_proaddress("lua_upvaluejoin"))(L, fidx1, n1, fidx2, n2);
}
void lua_sethook(lua_State* L, lua_Hook func, int mask, int count) {
	((decltype(lua_sethook)*)get_proaddress("lua_sethook"))(L, func, mask, count);
}
lua_Hook lua_gethook(lua_State* L) {
	return ((decltype(lua_gethook)*)get_proaddress("lua_gethook"))(L);
}
int lua_gethookmask(lua_State* L) {
	return ((decltype(lua_gethookmask)*)get_proaddress("lua_gethookmask"))(L);
}
int lua_gethookcount(lua_State* L) {
	return ((decltype(lua_gethookcount)*)get_proaddress("lua_gethookcount"))(L);
}
void luaL_checkversion_(lua_State* L, lua_Number ver, size_t sz) {
	((decltype(luaL_checkversion_)*)get_proaddress("luaL_checkversion_"))(L, ver, sz);
}
int luaL_getmetafield(lua_State* L, int obj, const char* e) {
	return ((decltype(luaL_getmetafield)*)get_proaddress("luaL_getmetafield"))(L, obj, e);
}
int luaL_callmeta(lua_State* L, int obj, const char* e) {
	return ((decltype(luaL_callmeta)*)get_proaddress("luaL_callmeta"))(L, obj, e);
}
const char* luaL_tolstring(lua_State* L, int idx, size_t* len) {
	return ((decltype(luaL_tolstring)*)get_proaddress("luaL_tolstring"))(L, idx, len);
}
int luaL_argerror(lua_State* L, int arg, const char* extramsg) {
	return ((decltype(luaL_argerror)*)get_proaddress("luaL_argerror"))(L, arg, extramsg);
}
const char* luaL_checklstring(lua_State* L, int arg,
	size_t* l) {
	return ((decltype(luaL_checklstring)*)get_proaddress("luaL_checklstring"))(L, arg, l);
}
const char* luaL_optlstring(lua_State* L, int arg,
	const char* def, size_t* l) {
	return ((decltype(luaL_optlstring)*)get_proaddress("luaL_optlstring"))(L, arg, def, l);
}
lua_Number luaL_checknumber(lua_State* L, int arg) {
	return ((decltype(luaL_checknumber)*)get_proaddress("luaL_checknumber"))(L, arg);
}
lua_Number luaL_optnumber(lua_State* L, int arg, lua_Number def) {
	return ((decltype(luaL_optnumber)*)get_proaddress("luaL_optnumber"))(L, arg, def);
}
lua_Integer luaL_checkinteger(lua_State* L, int arg) {
	return ((decltype(luaL_checkinteger)*)get_proaddress("luaL_checkinteger"))(L, arg);
}
lua_Integer luaL_optinteger(lua_State* L, int arg,
	lua_Integer def) {
	return ((decltype(luaL_optinteger)*)get_proaddress("luaL_optinteger"))(L, arg, def);
}
void luaL_checkstack(lua_State* L, int sz, const char* msg) {
	((decltype(luaL_checkstack)*)get_proaddress("luaL_checkstack"))(L, sz, msg);
}
void luaL_checktype(lua_State* L, int arg, int t) {
	((decltype(luaL_checktype)*)get_proaddress("luaL_checktype"))(L, arg, t);
}
void luaL_checkany(lua_State* L, int arg) {
	((decltype(luaL_checkany)*)get_proaddress("luaL_checkany"))(L, arg);
}
int   luaL_newmetatable(lua_State* L, const char* tname) {
	return ((decltype(luaL_newmetatable)*)get_proaddress("luaL_newmetatable"))(L, tname);
}
void  luaL_setmetatable(lua_State* L, const char* tname) {
	((decltype(luaL_setmetatable)*)get_proaddress("luaL_setmetatable"))(L, tname);
}
void* luaL_testudata(lua_State* L, int ud, const char* tname) {
	return ((decltype(luaL_testudata)*)get_proaddress("luaL_testudata"))(L, ud, tname);
}
void* luaL_checkudata(lua_State* L, int ud, const char* tname) {
	return ((decltype(luaL_checkudata)*)get_proaddress("luaL_checkudata"))(L, ud, tname);
}
void luaL_where(lua_State* L, int lvl) {
	((decltype(luaL_where)*)get_proaddress("luaL_where"))(L, lvl);
}
int luaL_error(lua_State* L, const char* fmt, ...) {
	return ((decltype(luaL_error)*)get_proaddress("luaL_error"))(L, fmt);
}
int luaL_checkoption(lua_State* L, int arg, const char* def,
	const char* const lst[]) {
	return ((decltype(luaL_checkoption)*)get_proaddress("luaL_checkoption"))(L, arg, def, lst);
}
int luaL_fileresult(lua_State* L, int stat, const char* fname) {
	return ((decltype(luaL_fileresult)*)get_proaddress("luaL_fileresult"))(L, stat, fname);
}
int luaL_execresult(lua_State* L, int stat) {
	return ((decltype(luaL_execresult)*)get_proaddress("luaL_execresult"))(L, stat);
}
int luaL_ref(lua_State* L, int t) {
	return ((decltype(luaL_ref)*)get_proaddress("luaL_ref"))(L, t);
}
void luaL_unref(lua_State* L, int t, int ref) {
	((decltype(luaL_unref)*)get_proaddress("luaL_unref"))(L, t, ref);
}
int luaL_loadfilex(lua_State* L, const char* filename,
	const char* mode) {
	return ((decltype(luaL_loadfilex)*)get_proaddress("luaL_loadfilex"))(L, filename, mode);
}
int luaL_loadbufferx(lua_State* L, const char* buff, size_t sz,
	const char* name, const char* mode) {
	return ((decltype(luaL_loadbufferx)*)get_proaddress("luaL_loadbufferx"))(L, buff, sz, name, mode);
}
int luaL_loadstring(lua_State* L, const char* s) {
	return ((decltype(luaL_loadstring)*)get_proaddress("luaL_loadstring"))(L, s);
}
lua_State* luaL_newstate(void) {
	return ((decltype(luaL_newstate)*)get_proaddress("luaL_newstate"))();
}
lua_Integer luaL_len(lua_State* L, int idx) {
	return ((decltype(luaL_len)*)get_proaddress("luaL_len"))(L, idx);
}
const char* luaL_gsub(lua_State* L, const char* s, const char* p,
	const char* r) {
	return ((decltype(luaL_gsub)*)get_proaddress("luaL_gsub"))(L, s, p, r);
}
void luaL_setfuncs(lua_State* L, const luaL_Reg* l, int nup) {
	((decltype(luaL_setfuncs)*)get_proaddress("luaL_setfuncs"))(L, l, nup);
}
int luaL_getsubtable(lua_State* L, int idx, const char* fname) {
	return ((decltype(luaL_getsubtable)*)get_proaddress("luaL_getsubtable"))(L, idx, fname);
}
void luaL_traceback(lua_State* L, lua_State* L1,
	const char* msg, int level) {
	((decltype(luaL_traceback)*)get_proaddress("luaL_traceback"))(L, L1, msg, level);
}
void luaL_requiref(lua_State* L, const char* modname,
	lua_CFunction openf, int glb) {
	((decltype(luaL_requiref)*)get_proaddress("luaL_requiref"))(L, modname, openf, glb);
}
void luaL_buffinit(lua_State* L, luaL_Buffer* B) {
	((decltype(luaL_buffinit)*)get_proaddress("luaL_buffinit"))(L, B);
}
char* luaL_prepbuffsize(luaL_Buffer* B, size_t sz) {
	return ((decltype(luaL_prepbuffsize)*)get_proaddress("luaL_prepbuffsize"))(B, sz);
}
void luaL_addlstring(luaL_Buffer* B, const char* s, size_t l) {
	((decltype(luaL_addlstring)*)get_proaddress("luaL_addlstring"))(B, s, l);
}
void luaL_addstring(luaL_Buffer* B, const char* s) {
	((decltype(luaL_addstring)*)get_proaddress("luaL_addstring"))(B, s);
}
void luaL_addvalue(luaL_Buffer* B) {
	((decltype(luaL_addvalue)*)get_proaddress("luaL_addvalue"))(B);
}
void luaL_pushresult(luaL_Buffer* B) {
	((decltype(luaL_pushresult)*)get_proaddress("luaL_pushresult"))(B);
}
void luaL_pushresultsize(luaL_Buffer* B, size_t sz) {
	((decltype(luaL_pushresultsize)*)get_proaddress("luaL_pushresultsize"))(B, sz);
}
char* luaL_buffinitsize(lua_State* L, luaL_Buffer* B, size_t sz) {
	return ((decltype(luaL_buffinitsize)*)get_proaddress("luaL_buffinitsize"))(L, B, sz);
}
void luaL_pushmodule(lua_State* L, const char* modname,
	int sizehint) {
	((decltype(luaL_pushmodule)*)get_proaddress("luaL_pushmodule"))(L, modname, sizehint);
}
void luaL_openlib(lua_State* L, const char* libname,
	const luaL_Reg* l, int nup) {
	((decltype(luaL_openlib)*)get_proaddress("luaL_openlib"))(L, libname, l, nup);
}
int luaopen_base(lua_State* L) {
	return ((decltype(luaopen_base)*)get_proaddress("luaopen_base"))(L);
}
int luaopen_coroutine(lua_State* L) {
	return ((decltype(luaopen_coroutine)*)get_proaddress("luaopen_coroutine"))(L);
}
int luaopen_table(lua_State* L) {
	return ((decltype(luaopen_table)*)get_proaddress("luaopen_table"))(L);
}
int luaopen_io(lua_State* L) {
	return ((decltype(luaopen_io)*)get_proaddress("luaopen_io"))(L);
}
int luaopen_os(lua_State* L) {
	return ((decltype(luaopen_os)*)get_proaddress("luaopen_os"))(L);
}
int luaopen_string(lua_State* L) {
	return ((decltype(luaopen_string)*)get_proaddress("luaopen_string"))(L);
}
int luaopen_utf8(lua_State* L) {
	return ((decltype(luaopen_utf8)*)get_proaddress("luaopen_utf8"))(L);
}
int luaopen_bit32(lua_State* L) {
	return ((decltype(luaopen_bit32)*)get_proaddress("luaopen_bit32"))(L);
}
int luaopen_math(lua_State* L) {
	return ((decltype(luaopen_math)*)get_proaddress("luaopen_math"))(L);
}
int luaopen_debug(lua_State* L) {
	return ((decltype(luaopen_debug)*)get_proaddress("luaopen_debug"))(L);
}
int luaopen_package(lua_State* L) {
	return ((decltype(luaopen_package)*)get_proaddress("luaopen_package"))(L);
}
void luaL_openlibs(lua_State* L) {
	((decltype(luaL_openlibs)*)get_proaddress("luaL_openlibs"))(L);
}

