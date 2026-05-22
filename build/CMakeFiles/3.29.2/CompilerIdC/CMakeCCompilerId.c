
/* cv-qualifiers did not exist in K&R C */

/* If the compiler does not have __has_include, pretend the answer is
   always no.  */


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
   /* _MSC_VER = VVRR */

/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
  /* _MSC_VER = VVRR */



  /* __BORLANDC__ = 0xVRR */

   /* __WATCOMC__ = VVRR */

   /* __WATCOMC__ = VVRP + 1100 */

   /* __SUNPRO_C = 0xVRRP */
   /* __SUNPRO_CC = 0xVRP */

  /* __HP_cc = VVRRPP */

  /* __DECC_VER = VVRRTPPPP */

  /* __IBMC__ = VRP */





  /* __IBMC__ = VRP */

  /* __IBMC__ = VRP */






  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */





/* __GHS_VERSION_NUMBER = VVVVRP */






  /* __ARMCC_VERSION = VRRPPPP */
  /* __ARMCC_VERSION = VRPPPP */


   /* _MSC_VER = VVRR */



   /* _MSC_VER = VVRR */



  /* _MSC_VER = VVRR */
    /* _MSC_FULL_VER = VVRRPPPPP */
    /* _MSC_FULL_VER = VVRRPPPP */

  /* __VERSIONNUM__ = 0xVVRRPPTT */


  /* SDCC = VRP */


/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */


/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";

char const* qnxnto = "INFO" ":" "qnxnto[]";

char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";


/* Identify known platforms by name.  */




































/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/















































/* Convert integer to decimal digit literals.  */
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
  '.', COMPILER_VERSION_MINOR,
   '.', COMPILER_VERSION_PATCH,
    '.', COMPILER_VERSION_TWEAK,
  ']','\0'};

/* Construct a string literal encoding the internal version number. */
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";

/* Construct a string literal encoding the version number components. */
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
  '.', SIMULATE_VERSION_MINOR,
   '.', SIMULATE_VERSION_PATCH,
    '.', SIMULATE_VERSION_TWEAK,
  ']','\0'};

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



const char* info_language_standard_default =
  "INFO" ":" "standard_default[" C_VERSION "]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
     defined(__TI_COMPILER_VERSION__)) &&                                     \
  !defined(__STRICT_ANSI__)
  "ON"
  "OFF"
"]";

/*--------------------------------------------------------------------------*/

void main() {}
int main(argc, argv) int argc; char *argv[];
int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
  require += info_version[argc];
  require += info_version_internal[argc];
  require += info_simulate[argc];
  require += info_simulate_version[argc];
  require += info_cray[argc];
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}
