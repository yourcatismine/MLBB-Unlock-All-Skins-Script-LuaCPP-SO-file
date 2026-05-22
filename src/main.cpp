

typedef int (*CanSelectSkin_t)(void* self);
typedef int (*CanEquipSkin_t)(void* self);
typedef int (*IsCanSelectSkin_t)(void* self);
typedef int (*IsCanEquipSkin_t)(void* self);

CanSelectSkin_t orig_CanSelectSkin = nullptr;
CanEquipSkin_t orig_CanEquipSkin = nullptr;
IsCanSelectSkin_t orig_IsCanSelectSkin = nullptr;
IsCanEquipSkin_t orig_IsCanEquipSkin = nullptr;

static int hook_CanSelectSkin(void* self) {
    LOGI("HOOK: CanSelectSkin called");
    return 1;
}

static int hook_CanEquipSkin(void* self) {
    LOGI("HOOK: CanEquipSkin called");
    return 1;
}

static int hook_IsCanSelectSkin(void* self) {
    LOGI("HOOK: IsCanSelectSkin called");
    return 1;
}

static int hook_IsCanEquipSkin(void* self) {
    LOGI("HOOK: IsCanEquipSkin called");
    return 1;
}

typedef void* (*il2cpp_domain_get_t)();
typedef void** (*il2cpp_domain_get_assemblies_t)(void* domain, size_t* size);
typedef void* (*il2cpp_assembly_get_image_t)(void* assembly);
typedef const char* (*il2cpp_image_get_name_t)(void* image);
typedef size_t (*il2cpp_image_get_class_count_t)(void* image);
typedef void* (*il2cpp_image_get_class_t)(void* image, size_t index);
typedef const char* (*il2cpp_class_get_name_t)(void* klass);
typedef void* (*il2cpp_class_get_fields_t)(void* klass, void** iter);
typedef const char* (*il2cpp_field_get_name_t)(void* field);
typedef void (*il2cpp_field_static_get_value_t)(void* field, void* value);
typedef void* (*il2cpp_class_get_methods_t)(void* klass, void** iter);
typedef const char* (*il2cpp_method_get_name_t)(void* method);
typedef void* (*il2cpp_method_get_function_pointer_t)(void* method);

static il2cpp_domain_get_t fn_domain_get;
static il2cpp_domain_get_assemblies_t fn_domain_get_assemblies;
static il2cpp_assembly_get_image_t fn_assembly_get_image;
static il2cpp_image_get_name_t fn_image_get_name;
static il2cpp_image_get_class_count_t fn_image_get_class_count;
static il2cpp_image_get_class_t fn_image_get_class;
static il2cpp_class_get_name_t fn_class_get_name;
static il2cpp_class_get_fields_t fn_class_get_fields;
static il2cpp_field_get_name_t fn_field_get_name;
static il2cpp_field_static_get_value_t fn_field_static_get_value;
static il2cpp_class_get_methods_t fn_class_get_methods = nullptr;
static il2cpp_method_get_name_t fn_method_get_name = nullptr;
static il2cpp_method_get_function_pointer_t fn_method_get_function_pointer = nullptr;

typedef int (*luaL_loadstring_fn)(void* L, const char* s);
typedef int (*lua_pcall_fn)(void* L, int nargs, int nresults, int errfunc);
typedef const char* (*lua_tolstring_fn)(void* L, int idx, size_t* len);
typedef void (*lua_settop_fn)(void* L, int idx);
typedef void (*lua_getglobal_fn)(void* L, const char* name);

static luaL_loadstring_fn lua_loadstring;
static lua_pcall_fn lua_pcall_f;
static lua_tolstring_fn lua_tolstring_f;
static lua_settop_fn lua_settop_f;
static lua_getglobal_fn lua_getglobal_f;

static bool resolve(void* h) {
    fn_domain_get = (il2cpp_domain_get_t)dlsym(h, "il2cpp_domain_get");
    fn_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)dlsym(h, "il2cpp_domain_get_assemblies");
    fn_assembly_get_image = (il2cpp_assembly_get_image_t)dlsym(h, "il2cpp_assembly_get_image");
    fn_image_get_name = (il2cpp_image_get_name_t)dlsym(h, "il2cpp_image_get_name");
    fn_image_get_class_count = (il2cpp_image_get_class_count_t)dlsym(h, "il2cpp_image_get_class_count");
    fn_image_get_class = (il2cpp_image_get_class_t)dlsym(h, "il2cpp_image_get_class");
    fn_class_get_name = (il2cpp_class_get_name_t)dlsym(h, "il2cpp_class_get_name");
    fn_class_get_fields = (il2cpp_class_get_fields_t)dlsym(h, "il2cpp_class_get_fields");
    fn_field_get_name = (il2cpp_field_get_name_t)dlsym(h, "il2cpp_field_get_name");
    fn_field_static_get_value = (il2cpp_field_static_get_value_t)dlsym(h, "il2cpp_field_static_get_value");
    fn_class_get_methods = (il2cpp_class_get_methods_t)dlsym(h, "il2cpp_class_get_methods");
    fn_method_get_name = (il2cpp_method_get_name_t)dlsym(h, "il2cpp_method_get_name");
    fn_method_get_function_pointer = (il2cpp_method_get_function_pointer_t)dlsym(h, "il2cpp_method_get_function_pointer");
    
    LOGI("Method APIs: get_methods=%p, get_name=%p, get_fn=%p", fn_class_get_methods, fn_method_get_name, fn_method_get_function_pointer);
    return fn_domain_get && fn_field_static_get_value;
}

static bool execLua(void* L, const char* code, const char* label) {
    if (!L) {
        LOGE("[%s] L is null", label);
        return false;
    }
    if (!lua_loadstring) {
        LOGE("[%s] lua_loadstring is null", label);
        return false;
    }
    int r = lua_loadstring(L, code);
    if (r != 0) {
        const char* e = lua_tolstring_f ? lua_tolstring_f(L, -1, nullptr) : "?";
        LOGE("[%s] load: %s", label, e ? e : "?");
        if (lua_settop_f) lua_settop_f(L, -2);
        return false;
    }
    r = lua_pcall_f(L, 0, 0, 0);
    if (r != 0) {
        const char* e = lua_tolstring_f ? lua_tolstring_f(L, -1, nullptr) : "?";
        LOGE("[%s] exec: %s", label, e ? e : "?");
        if (lua_settop_f) lua_settop_f(L, -2);
        return false;
    }
    LOGI("[%s] OK", label);
    return true;
}

static void logLuaStr(void* L, const char* varname) {
    if (!lua_getglobal_f || !lua_tolstring_f) return;
    lua_getglobal_f(L, varname);
    const char* s = lua_tolstring_f(L, -1, nullptr);
    if (s) {
        int len = strlen(s);
        for (int i = 0; i < len; i += 900) {
            char buf[1024];
            int n = len - i > 900 ? 900 : len - i;
            memcpy(buf, s + i, n); buf[n] = 0;
            LOGI("%s[%d]: %s", varname, i, buf);
        }
    } else {
        LOGI("%s: (nil)", varname);
    }
    if (lua_settop_f) lua_settop_f(L, -2);
}

static void* findStaticField(void* klass, const char* name) {
    void* iter = nullptr; void* f;
    while ((f = fn_class_get_fields(klass, &iter))) {
        const char* fn = fn_field_get_name(f);
        if (fn && strcmp(fn, name) == 0) return f;
    }
    return nullptr;
}

static void* hook_thread(void*) {
    LOGI("=== v24 SKIN SELECTION HOOK ===");

    void* il2cpp = nullptr;
    for (int a = 0; a < 120; a++) {
        FILE* maps = fopen("/proc/self/maps", "r");
        if (maps) {
            char line[512];
            while (fgets(line, sizeof(line), maps)) {
                if (strstr(line, "libcsharp.so")) {
                    char* p = strstr(line, "/");
                    if (p) {
                        char* nl = strchr(p, '\n'); if (nl) *nl = 0;
                        void* h = dlopen(p, RTLD_NOLOAD);
                        if (h && dlsym(h, "il2cpp_domain_get")) {
                            il2cpp = h; fclose(maps); goto found;
                        }
                    }
                }
            }
            fclose(maps);
        }
        if (a % 10 == 0) LOGI("Wait... (%d)", a);
        sleep(1);
    }
    LOGI("Not HybridCLR, exit."); return nullptr;

found:
    if (!resolve(il2cpp)) { LOGE("resolve fail"); return nullptr; }

    void* libmoba = nullptr;
    FILE* maps = fopen("/proc/self/maps", "r");
    if (maps) {
        char line[512];
        while (fgets(line, sizeof(line), maps)) {
            if (strstr(line, "libmoba.so")) {
                char* p = strstr(line, "/");
                if (p) {
                    char* nl = strchr(p, '\n'); if (nl) *nl = 0;
                    libmoba = dlopen(p, RTLD_NOLOAD);
                    if (libmoba) break;
                }
            }
        }
        fclose(maps);
    }
    if (!libmoba) { LOGE("No libmoba"); return nullptr; }

    lua_loadstring = (luaL_loadstring_fn)dlsym(libmoba, "luaL_loadstring");
    lua_pcall_f = (lua_pcall_fn)dlsym(libmoba, "lua_pcall");
    if (!lua_pcall_f) lua_pcall_f = (lua_pcall_fn)dlsym(libmoba, "lua_pcallk");
    lua_tolstring_f = (lua_tolstring_fn)dlsym(libmoba, "lua_tolstring");
    lua_settop_f = (lua_settop_fn)dlsym(libmoba, "lua_settop");
    lua_getglobal_f = (lua_getglobal_fn)dlsym(libmoba, "lua_getglobal");
    if (!lua_loadstring || !lua_pcall_f) { LOGE("No Lua API"); return nullptr; }
    LOGI("Lua API ready");

    void* img = nullptr;
    for (int w = 0; w < 60; w++) {
        void* dom = fn_domain_get(); if (!dom) { sleep(1); continue; }
        size_t cnt = 0; void** asms = fn_domain_get_assemblies(dom, &cnt);
        for (size_t i = 0; i < cnt; i++) {
            void* im = fn_assembly_get_image(asms[i]); if (!im) continue;
            const char* n = fn_image_get_name(im);
            if (n && strcmp(n, "Assembly-CSharp.dll") == 0) { img = im; goto fa; }
        }
        sleep(1);
    }
fa: if (!img) { LOGE("No asm"); return nullptr; }

    LOGI("Waiting 40s for full init...");
    sleep(40);

    LOGI("Starting BROAD native il2cpp scan (all classes)...");
    size_t cc = fn_image_get_class_count(img);
    int nativeHookCount = 0;

    const char* targetClasses[] = {"ChooseHeroMgr", "get_bOwned", "ChooseHeroComp", "ChooseHeroCompMgr", nullptr};
    const char* trueMethodNames[] = {"IsSkinUseable", "BFreeSkin", "BActFreeSkin", "BLuckyBoyFreeSkin",
        "BCloneModeFreeSkin", "BCustomRoomFreeSkin", "IsCanExpSkin",
        "HasExperienceSkinCard", "IsActFreenSkin", "IsFlowbackShareSkin",
        "CheckColorSkinEnableUse", "IsShareSkinFromOtherPlayer",
        "CheckSkinEnableShareFromOther", "CanUseHero",
        "IsAvailableHero", "IsChooseSkin", "IsCheckSkin", nullptr};
    const char* falseMethodNames[] = {"CheckHideSkinIcon", "IsShowLimitTime",
        "IsHeroDefaultSkin", "IsHeroLockByFirstSeason", nullptr};

    if (fn_class_get_methods && fn_method_get_name) {
        for (size_t i = 0; i < cc; i++) {
            void* k = fn_image_get_class(img, i); if (!k) continue;
            const char* cn = fn_class_get_name(k);
            if (!cn) continue;

            void* iter = nullptr;
            void* method;
            while ((method = fn_class_get_methods(k, &iter))) {
                const char* mn = fn_method_get_name(method);
                if (!mn) continue;

                for (int mi = 0; trueMethodNames[mi]; mi++) {
                    if (strcmp(mn, trueMethodNames[mi]) == 0) {
                        void** methodPtr = (void**)method;
                        void* origFn = methodPtr[0];
                        uintptr_t page = (uintptr_t)methodPtr & ~0xFFF;
                        if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE) == 0) {
                            methodPtr[0] = (void*)hook_CanSelectSkin;
                            nativeHookCount++;
                            LOGI("[T] %s.%s orig=%p", cn, mn, origFn);
                        }
                        break;
                    }
                }

                for (int mi = 0; falseMethodNames[mi]; mi++) {
                    if (strcmp(mn, falseMethodNames[mi]) == 0) {
                        void** methodPtr = (void**)method;
                        void* origFn = methodPtr[0];
                        uintptr_t page = (uintptr_t)methodPtr & ~0xFFF;
                        if (mprotect((void*)page, 0x2000, PROT_READ | PROT_WRITE) == 0) {
                            methodPtr[0] = (void*)(int(*)(void*))([](void* s) -> int { return 0; });
                            nativeHookCount++;
                            LOGI("[F] %s.%s orig=%p", cn, mn, origFn);
                        }
                        break;
                    }
                }
            }
        }
    }
    LOGI("Native il2cpp hooks applied: %d", nativeHookCount);

    LOGI("Starting skin ownership discovery...");
    int discCount = 0;
    for (size_t i = 0; i < cc && discCount < 200; i++) {
        void* k = fn_image_get_class(img, i); if (!k) continue;
        const char* cn = fn_class_get_name(k);
        if (!cn) continue;

        void* iter = nullptr;
        void* method;
        while ((method = fn_class_get_methods(k, &iter)) && discCount < 200) {
            const char* mn = fn_method_get_name(method);
            if (!mn || strlen(mn) < 4) continue;

            bool hasSkin = (strstr(mn, "Skin") || strstr(mn, "skin"));
            bool hasOwn = (strstr(mn, "Own") || strstr(mn, "Have") || strstr(mn, "Buy") ||
                           strstr(mn, "Lock") || strstr(mn, "Unlock") || strstr(mn, "Free") ||
                           strstr(mn, "Owned") || strstr(mn, "Useable") || strstr(mn, "Usable") ||
                           strstr(mn, "Available") || strstr(mn, "Equip") || strstr(mn, "Select"));

            if (hasSkin && hasOwn) {
                LOGI("[DISC] %s.%s", cn, mn);
                discCount++;
            }
        }
    }
    LOGI("Discovery found %d skin methods", discCount);

    void* luaMgrClass = nullptr;
    for (size_t i = 0; i < cc; i++) {
        void* k = fn_image_get_class(img, i); if (!k) continue;
        const char* cn = fn_class_get_name(k);
        if (cn && strcmp(cn, "LuaScriptMgr") == 0) { luaMgrClass = k; break; }
    }
    if (!luaMgrClass) { LOGE("No LuaScriptMgr"); return nullptr; }

    void* instanceField = findStaticField(luaMgrClass, "<Instance>k__BackingField");
    if (!instanceField) { LOGE("No field"); return nullptr; }

    void* mgrInstance = nullptr;
    fn_field_static_get_value(instanceField, &mgrInstance);
    if (!mgrInstance) { LOGE("Instance null"); return nullptr; }

    void* luaStateObj = *(void**)((char*)mgrInstance + 0x10);
    if (!luaStateObj) { LOGE("LuaState null"); return nullptr; }

    void* L = *(void**)((char*)luaStateObj + 0x10);
    if (!L) { LOGE("L null"); return nullptr; }
    LOGI(">>> lua_State* = %p", L);

    LOGI("Starting combined class+instance __index hook...");
    execLua(L,
        "local c=0 "
        "local yes={} local no={} "
        "local yt={'IsSkinUseable','AllSkinUnLock','CheckColorSkinEnableUse','IsChooseSkin','IsCheckSkin','CheckSkinEnableShareFromOther','IsSkinEnable','IsHaveSkin','IsHaveSkinForever','IsSkinOwn','IsOwnSkin','IsSkinOwned','IsOwnedSkin','HasOwnedSkin','HasSkin','IsSkinBuy','IsSkinUnlock','CheckSkinOwn','IsSkinValid','IsSkinAvailable','CanUseSkin','IsHaveCostume','IsCostumeOwn','IsHeroSkinOwn','IsEquipSkin','IsHaveHeroSkin','IsSkinPermanent','IsSkinCanUse','CanSelectSkin','CanEquipSkin','CheckSkinPermission','IsPaintedSkinOwn','HasPaintedSkin','IsPaintedSkinUnlock','IsPaintedSkinAvailable','IsPaintedSkinValid','IsPaintedSkinUseable','CanUsePaintedSkin','IsHavePaintedSkin','CheckPaintedSkinOwn','CanSelectHeroSkin','CanEquipHeroSkin','CanUseHeroSkin','IsHeroSkinAvailable','IsHeroSkinUnlocked','CheckHeroSkinOwn','IsHeroSkinEnable','CanTrySkin','IsSkinCanTry','HeroCanUse','CanUseHero','IsAvailableHero'} "
        "local nt={'CheckHeroOrSkinIsInvaild','IsSkinExpired','IsSkinLocked','IsSkinTimeLimit','IsSkinTimeLimited','IsSkinDisabled','IsPaintedSkinLocked','IsPaintedSkinExpired','IsPaintedSkinDisabled','IsHeroSkinLocked','IsHeroSkinExpired','IsHeroSkinDisabled','IsNeedUnlock','IsNeedBuyFirst','NeedShowBuyBtn','NeedShowPurchaseBtn','IsShowBuyButton','IsShowPurchaseButton','IsShowBuy','IsShowPurchase','NeedBuy','NeedPurchase','ShouldShowBuyBtn','ShouldShowPurchaseBtn','IsNeedBuy','IsNeedPurchase','CheckHideSkinIcon','IsShowLimitTime'} "
        "for i=1,#yt do yes[yt[i]]=true end "
        "for i=1,#nt do no[nt[i]]=true end "
        "local fn_true=function(...) return true end "
        "local fn_false=function(...) return false end "

        "local C={'ChooseHeroMgr','SystemData','UIFuncs','CmdHeroSkin','IndividualDataSet'} "
        "for i=1,#C do "
        "local cls=rawget(_G,C[i]) "
        "if cls then "
        "local mt=getmetatable(cls) "
        "if mt and type(rawget(mt,'__index'))=='function' then "
        "local orig=rawget(mt,'__index') "
        "rawset(mt,'__index',function(t,k) "
        "if yes[k] then return fn_true end "
        "if no[k] then return fn_false end "
        "return orig(t,k) "
        "end) "
        "c=c+1 "
        "end end end "

        "pcall(function() "
        "for i=1,#C do "
        "local cls=rawget(_G,C[i]) "
        "if cls then "
        "local ok,inst=pcall(function() return cls.Instance end) "
        "if ok and inst and type(inst)=='userdata' then "
        "local imt=getmetatable(inst) "
        "if imt and rawget(imt,'__index') then "
        "local iidx=rawget(imt,'__index') "
        "if type(iidx)=='function' then "
        "local iorig=iidx "
        "rawset(imt,'__index',function(t,k) "
        "if yes[k] then return fn_true end "
        "if no[k] then return fn_false end "
        "return iorig(t,k) "
        "end) "
        "c=c+1 "
        "end end end end end end) "

        "local P={'BagDataManager','HerolistMgr'} "
        "for i=1,#P do local t=rawget(_G,P[i]) if t and type(t)=='table' then "
        "for j=1,#yt do rawset(t,yt[j],fn_true) end "
        "for j=1,#nt do rawset(t,nt[j],fn_false) end "
        "c=c+1 end end "
        "_G._sh=c",
        "Hook"
    );
    logLuaStr(L, "_sh");

    LOGI("=== ALL HOOKS APPLIED ===");
    LOGI("Hook thread complete");
    return nullptr;
}

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("=== v24 ===");
    pthread_t t; pthread_create(&t, nullptr, hook_thread, nullptr); pthread_detach(t);
    return JNI_VERSION_1_6;
}
