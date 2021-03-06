/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;	/* 1 means swallow flating windows by default*/
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
//static const char *fonts[]          = { "Liberation Mono:size=10" };
//static const char dmenufont[]       = "Liberation Mono:size=10";
static const char *fonts[]          = { "Source Code Pro:style=Bold:size=9", "FontAwesome:Regular:pixelsize=12" };
static const char dmenufont[]       = "Source Code Pro:style=Bold:size=9";
static const char col_gray1[]       = "#222222";	/* status not selected */
static const char col_gray2[]       = "#444444";	/* tag    not selected */
static const char col_gray3[]       = "#BBBBBB";	/* icon   not selected */
static const char col_gray4[]       = "#EEEEEE";	/* icon text  selected */
static const char col_cyan[]        = "#8ABAB7";	/* status tag selected */
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray1, col_cyan, col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const char *tags[] = { "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask  isfloating  isterminal  noswallow  monitor */
	//{ "Gimp",   NULL,       NULL,       0,         1,          0,          0,         -1 },
	{ "Chromium", NULL,       NULL,       1 << 1,    0,          0,          -1,        -1 },
	{ NULL,       NULL,       "nmtui",    0,         1,          0,          0,         -1 }, /* used for networkmanager */
	{ NULL,       NULL,       "ranger",   0,         1,          0,          0,         -1 }, /* file manager */
	{ NULL,       NULL,       "pulsemixer", 0,       1,          0,          0,         -1 }, /* sound */
        { "Blueman-manager", NULL, NULL,      0,         1,          0,          0,         -1 }, /* bluetooth */
	{ "plexmediaplayer", NULL, NULL,      1 << 3,    0,          0,          0,         -1 }, /* plex */
	{ "st-256color", NULL,    NULL,       0,         0,          1,          0,         -1 }, /* terminal */
	{ NULL,       NULL,       "Event Tester", 0,     0,          0,          1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray1, "-c", "-l", "15", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *rangercmd[] = { "st", "ranger", NULL };
static const char *pulsecmd[] = { "st", "pulsemixer", NULL };
static const char *chromecmd[] = { "chromium" , NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,			XK_Left,   focusstack,     {.i = +1 } }, /*navigate w. arrow*/
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,			XK_Right,  focusstack,     {.i = +1 } }, /*navigate w. arrow*/
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_agrave, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,      {.i = +1 } },
	{ MODKEY,			XK_n,	   shiftview,	   {.i = +1 } }, /*shiftview*/
	{ MODKEY,			XK_b,	   shiftview,	   {.i = -1 } }, /*shiftview*/
	{ MODKEY,			XK_minus,  setgaps,        {.i = -1 } }, /*fullgaps*/
	{ MODKEY, 			XK_equal,  setgaps,	   {.i = +1 } }, /*fullgaps*/
        { MODKEY|ShiftMask,		XK_equal,  setgaps, 	   {.i = 0 } }, /*fullgaps*/
	{ MODKEY|ShiftMask,		XK_j,	   pushdown,	   {0} }, /*push*/
	{ MODKEY|ShiftMask,		XK_Left,   pushdown,	   {0} }, /*push with arrow*/
	{ MODKEY|ShiftMask,		XK_k,	   pushup,	   {0} }, /*push*/
	{ MODKEY|ShiftMask,		XK_Right,  pushup,	   {0} }, /*push with arrow*/
	TAGKEYS(                        XK_ampersand,              0)
	TAGKEYS(                        XK_eacute,                 1)
	TAGKEYS(                        XK_quotedbl,               2)
	TAGKEYS(                        XK_apostrophe,             3)
	TAGKEYS(                        XK_parenleft,              4)
	//TAGKEYS(                        XK_section,                5)
	//TAGKEYS(                        XK_egrave,                 6)
	//TAGKEYS(                        XK_exclam,                 7)
	//TAGKEYS(                        XK_ccedilla,               8)
	{ MODKEY|ShiftMask,             XK_Escape, quit,           {0} },
	{ MODKEY,			XK_r,	   spawn,	   {.v = rangercmd } },
	{ MODKEY,			XK_p,	   spawn,	   {.v = pulsecmd } },
	{ MODKEY,			XK_c,	   spawn,	   {.v = chromecmd } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} }, /* statuscmd blocks click */
	/*ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} }, // statuscmd blocks click */
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} }, /* statuscmd blocks click */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

