#ifndef _XLOCALE_H_
#define _XLOCALE_H_

struct xlocale_refcounted {
	/** Number of references to this component.  */
	long retain_count;
	/** Function used to destroy this component, if one is required*/
	void(*destructor)(void*);
};

enum {
	XLC_COLLATE = 0,
	XLC_CTYPE,
	XLC_MONETARY,
	XLC_NUMERIC,
	XLC_TIME,
	XLC_MESSAGES,
	XLC_LAST
};

#define ENCODING_LEN 31
#define CATEGORY_LEN 11

#define XLOCALE_DEF_VERSION_LEN 12

/**
 * Header for a locale component.  All locale components must begin with this
 * header.
 */
struct xlocale_component {
	struct xlocale_refcounted header;
	/** Name of the locale used for this component. */
	char locale[ENCODING_LEN+1];
	/** Version of the definition for this component. */
	char version[XLOCALE_DEF_VERSION_LEN];
};

// typedef struct lconv lconv;

/**
 * xlocale structure, stores per-thread locale information.  
 */
typedef struct locale_t {
	struct xlocale_refcounted header;
	/** Components for the locale.  */
	struct xlocale_component *components[XLC_LAST];
	/** Flag indicating if components[XLC_MONETARY] has changed since the
	 * last call to localeconv_l() with this locale. */
	int monetary_locale_changed;
	/** Flag indicating whether this locale is actually using a locale for
	 * LC_MONETARY (1), or if it should use the C default instead (0). */
	int using_monetary_locale;
	/** Flag indicating if components[XLC_NUMERIC] has changed since the
	 * last call to localeconv_l() with this locale. */
	int numeric_locale_changed;
	/** Flag indicating whether this locale is actually using a locale for
	 * LC_NUMERIC (1), or if it should use the C default instead (0). */
	int using_numeric_locale;
	/** Flag indicating whether this locale is actually using a locale for
	 * LC_TIME (1), or if it should use the C default instead (0). */
	int using_time_locale;
	/** Flag indicating whether this locale is actually using a locale for
	 * LC_MESSAGES (1), or if it should use the C default instead (0). */
	int using_messages_locale;
	/** The structure to be returned from localeconv_l() for this locale. */
	//lconv lconv;
	/** Buffer used by nl_langinfo_l() */
	char *csym;
} locale_t;

#endif
