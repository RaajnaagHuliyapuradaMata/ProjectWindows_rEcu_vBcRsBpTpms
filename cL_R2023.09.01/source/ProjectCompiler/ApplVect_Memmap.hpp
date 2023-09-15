

#if defined( FBLBMHDR_BMHEADER_START_SEC_CONST )
# pragma ghs section rodata=".FBLBMHEADERHDR"
# pragma ghs startdata
# undef FBLBMHDR_BMHEADER_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLBMHDR_BMHEADER_STOP_SEC_CONST )
# pragma ghs enddata
# pragma ghs section rodata=default
# undef FBLBMHDR_BMHEADER_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHEADER_START_SEC_CONST )
# pragma ghs section rodata=".FBLHEADER"
# pragma ghs startdata
# undef FBLHEADER_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBLHEADER_STOP_SEC_CONST )
# pragma ghs enddata
# pragma ghs section rodata=default
# undef FBLHEADER_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_APPLVECT_START_SEC_CONST )
# pragma ghs startdata
# pragma ghs section rodata=".APPLVECT"
# undef FBL_APPLVECT_START_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif

#if defined( FBL_APPLVECT_STOP_SEC_CONST )
   # pragma ghs section
   # pragma ghs enddata
# undef FBL_APPLVECT_STOP_SEC_CONST
# undef FBL_MEMMAP_ERROR
#endif
