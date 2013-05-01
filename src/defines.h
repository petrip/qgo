/***************************************************************************
 *   Copyright (C) 2009 by The qGo Project                                 *
 *                                                                         *
 *   This file is part of qGo.   					   *
 *                                                                         *
 *   qGo is free software: you can redistribute it and/or modify           *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 *   or write to the Free Software Foundation, Inc.,                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#ifndef DEFINES_H
#define DEFINES_H

#include "audio.h"

#include <QtCore>

/*
* Global defines
*/

#define PACKAGE "qGo"
#define VERSION "2.0.0"

#define DEFAULT_BOARD_SIZE 19
#define BOARD_X 500
#define BOARD_Y 500

#define WHITE_STONES_NB 8

#define SLIDER_INIT 0

#define CONSOLECMDPREFIX "--->"

//3 looked a little small
#define SMALL_STONE_TERR_DIVISOR	2.5

/*
* GNUgo default level
*/
#define GNUGO_LEVEL 10

/* Game refusal motives... like we need a reason.  */
#define	GD_REFUSE_NOTOPEN		0
#define GD_REFUSE_DECLINE		1
#define GD_REFUSE_CANCEL		2
#define GD_REFUSE_INGAME		3
#define GD_REFUSE_NODIRECT		4
#define GD_INVALID_PARAMETERS		5
#define GD_OPP_NO_NMATCH		6
#define GD_RESET			7

/* NetworkDispatch codes */
#define ND_CONNECTED			1
#define ND_WAITING			0
#define ND_BADLOGIN			-1
#define ND_BADPASSWORD			-2
#define ND_BADHOST			-3
#define ND_BADCONNECTION		-4		//something of a default
#define ND_PROTOCOL_ERROR		-5
#define ND_USERCANCELED			-6
#define ND_ALREADYLOGGEDIN		-7
#define ND_CONN_REFUSED			-8

/*
* Enum definitions
*/
enum StoneColor { stoneNone, stoneWhite, stoneBlack, stoneErase };
enum GameMode { modeNormal, modeObserve, modeMatch, modeTeach, modeComputer, modeReview, modeUndefined };
enum GamePhase { phaseInit, phaseOngoing, phaseEdit, phaseNavTo, phaseScore, phaseEnded};
enum MarkType { markNone, markSquare, markCircle, markTriangle, markCross, markText, markNumber, markTerrBlack, markTerrWhite, markKoMarker };
enum Codec { codecNone, codecBig5, codecEucJP, codecJIS, codecSJIS, codecEucKr, codecGBK, codecTscii };
enum Language { None, German, French, Italian, Danish, Dutch, Czech, Chinese, Portugese, Polish, Russian, Turkish };
enum player_type {HUMAN=0,COMPUTER} ;
enum assessType { noREQ, FREE, RATED, TEACHING };

enum State { stateVarBegin, stateNode, stateVarEnd };
enum Property { moveBlack, moveWhite, editBlack, editWhite, editErase, comment, editMark, unknownProp, nodeName, timeLeft, openMoves, nextMove};
enum TimeSystem { none, absolute, byoyomi, canadian, tvasia };

/*
 * Game server enums
 */
/* ConnectionType in line with ui comboBox_server entry. FIXME to make more securely connected */
enum ConnectionType { TypeNone = 0, TypeIGS, TypeWING, TypeLGS,
			 TypeORO,
			 TypeTYGEM, TypeEWEIQI, TypeTOM,
			TypeUNKNOWN, TypeNNGS, TypeCTN, TypeCWS, TypeDEFAULT };
// TypeCyberORO?? just IGS, and CyberORO, instead of with Type?? FIXME

/*
* Global structs
*/
struct ASCII_Import
{
	char blackStone, whiteStone, starPoint, emptyPoint, hBorder, vBorder;
};

struct MatrixStone
{
	int x, y;
	StoneColor c;
	MatrixStone() {};
	MatrixStone(int _x, int _y, StoneColor _c) : x(_x), y(_y), c(_c) {};
};

/* This should really probably have access functions or
 * something and then friend the mainwindow settings code so
 * that only it can change it */
struct _preferences
{
	bool nmatch_black;
	bool nmatch_white;
	bool nmatch_nigiri;
	QString nmatch_handicap;
	bool draw_ko_marker;
    bool use_chat_widget;
	bool number_current_move;
	bool terr_stone_mark;
	bool observe_outside_on_doubleclick;

	int playerslist_sortcolumn;
	bool playerslist_sortascending;
	int gameslist_sortcolumn;
	bool gameslist_sortascending;

	int default_size;
	int default_komi;
	bool warn_about_codecs;
	bool simple_player_names;
	
	int default_stonesmaintime;
	int default_stonestime;
	int default_stones;
	int default_byomaintime;
	int default_byoperiodtime;
	int default_byoperiods;
	int default_asiamaintime;
	int default_asiaperiodtime;
	int default_asiaperiods;
	void fill(void)
	{
		QSettings settings;
		QVariant var;
		
		nmatch_black = settings.value("NMATCH_BLACK").toBool();
		nmatch_white = settings.value("NMATCH_WHITE").toBool();
		nmatch_nigiri = settings.value("NMATCH_NIGIRI").toBool();
		nmatch_handicap = settings.value("NMATCH_HANDICAP").toString();
		
		draw_ko_marker = (settings.value("KOMARKER") == 1);
        use_chat_widget = (settings.value("CHATWIDGETOFF") != 1);
		number_current_move = (settings.value("NUMBER_CURRENT_MOVE") == 1);
		terr_stone_mark = (settings.value("TERR_STONE_MARK") == 1);
		observe_outside_on_doubleclick = (settings.value("OBSERVEOUTSIDE") == 1);
		
		playerslist_sortcolumn = settings.value("PLAYERSLIST_SORTCOLUMN").toInt();
		playerslist_sortascending = settings.value("PLAYERSLIST_SORTASCENDING").toBool();
		gameslist_sortcolumn = settings.value("GAMESLIST_SORTCOLUMN").toInt();
		gameslist_sortascending = settings.value("GAMESLIST_SORTASCENDING").toBool();

		default_size = settings.value("DEFAULT_SIZE").toInt();
		default_komi = settings.value("DEFAULT_KOMI").toInt();
		simple_player_names = settings.value("SIMPLEPLAYERNAMES").toBool();
		
		warn_about_codecs = !settings.value("DONT_WARN_ABOUT_CODECS").toBool();
		
		if((var = settings.value("DEFAULT_STONESMAIN")) == QVariant())
			default_stonesmaintime = 600;
		else
			default_stonesmaintime = var.toInt();
		if((var = settings.value("DEFAULT_STONEST")) == QVariant())
			default_stonestime = 600;
		else
			default_stonestime = var.toInt();
		if((var = settings.value("DEFAULT_STONES")) == QVariant())
			default_stones = 25;
		else
			default_stones = var.toInt();
		if((var = settings.value("DEFAULT_BYOMAIN")) == QVariant())
			default_byomaintime = 600;
		else
			default_byomaintime = var.toInt();
		if((var = settings.value("DEFAULT_BYOPERIODT")) == QVariant())
			default_byoperiodtime = 30;
		else
			default_byoperiodtime = var.toInt();
		if((var = settings.value("DEFAULT_BYOPERIODS")) == QVariant())
			default_byoperiods = 3;
		else
			default_byoperiods = var.toInt();
		if((var = settings.value("DEFAULT_TVASIAMAIN")) == QVariant())
			default_asiamaintime = 30;
		else
			default_asiamaintime = var.toInt();
		if((var = settings.value("DEFAULT_TVASIAPERIODT")) == QVariant())
			default_asiaperiodtime = 30;
		else
			default_asiaperiodtime = var.toInt();
		if((var = settings.value("DEFAULT_TVASIAPERIODS")) == QVariant())
			default_asiaperiods = 4;
		else
			default_asiaperiods = var.toInt();
		
		
	}
	void save(void)
	{
		QSettings settings;
		
		settings.setValue("PLAYERSLIST_SORTCOLUMN", playerslist_sortcolumn);
		settings.setValue("PLAYERSLIST_SORTASCENDING", playerslist_sortascending);
		settings.setValue("GAMESLIST_SORTCOLUMN", gameslist_sortcolumn);
		settings.setValue("GAMESLIST_SORTASCENDING", gameslist_sortascending);
		
		settings.setValue("DONT_WARN_ABOUT_CODECS", !warn_about_codecs);

		settings.setValue("DEFAULT_STONESMAIN", default_stonesmaintime);
		settings.setValue("DEFAULT_STONEST", default_stonestime);
		settings.setValue("DEFAULT_STONES", default_stones);
		settings.setValue("DEFAULT_BYOMAIN", default_byomaintime);
		settings.setValue("DEFAULT_BYOPERIODT", default_byoperiodtime);
		settings.setValue("DEFAULT_BYOPERIODS", default_byoperiods);
		settings.setValue("DEFAULT_TVASIAMAIN", default_asiamaintime);
		settings.setValue("DEFAULT_TVASIAPERIODT", default_asiaperiodtime);
		settings.setValue("DEFAULT_TVASIAPERIODS", default_asiaperiods);
	}
};

/* There's only one of each of these, and they're both
 * used in weird places, so we'll make them global */
extern _preferences preferences;
extern class MainWindow * mainwindow;
extern class ConnectionWidget * connectionWidget;

#ifdef Q_WS_WIN
extern QString applicationPath;
#endif

/* Non alsa, i.e., windows and mac use QSound which cannot use embedded resources.
 * Phonon fixes this but it doesn't compile with mingw on windows.  So Sounds will
 * only be embedded on linux and mac and windows will have to install them. */
#ifdef Q_OS_LINUX
	#define SOUND_PATH_PREFIX			":/ressources/sounds/"
	#define TRANSLATIONS_PATH_PREFIX		"/usr/share/qgo/languages/"
#elif defined(Q_OS_MAC)
	#define SOUND_PATH_PREFIX			"qGo.app/Contents/Resources/Sounds/"
	#define TRANSLATIONS_PATH_PREFIX		"qGo.app/Contents/Resources/Translations/"
#else //Q_OS_WIN or Q_WSWIN?
	#define SOUND_PATH_PREFIX			"sounds/"
	#define TRANSLATIONS_PATH_PREFIX		"translations/"
#endif

void startqGo(void);

#endif
