#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"

#define DEFAULT_COLOR -1

#define TAB_COLOR 1 /* YOU CANT DEFINE ONE AS `0` (dumbass) */
#define TAB_TEXT 2
#define TAB_TEXT_HIGH 3

#define SHOP_INDEX 21
#define SHOP_NAME 22
#define SHOP_SHORT_DESC 23
#define SHOP_PRICE 24
#define SHOP_STAR_ON 25
#define SHOP_STAR_OFF 26
#define SHOP_ON_SALE 27
#define SHOP_INFO 28


struct product {
  float price;
  float rating;
  bool onsale;
  char *name;
  char *description;
};

int main() {
	int ch, row, col;
	int tab = 0;
	bool running = true;

	char typingbuffer[256] = "";
	int pointer = 0;
	bool typing = false;

	char tabs[4][20] = { "[S]hop", "[C]art", "[O]rder", "S[e]rver" };

	int amountoftabs = sizeof(tabs)/sizeof(tabs[0]);

	struct product shop_products[64]; /* im not making a pointer to an array of structs because kms no */
	shop_products[0].price = 9.99;
	shop_products[0].rating = 3.2;
	shop_products[0].onsale = false;
	shop_products[0].name = "This is a product";
	shop_products[0].description = "This is the product desctription. dhuisahisfhsdifhdsuifdsifsdi ghivbfdigsfji fijg ihgifdhgis griefirehfuiregei rugiruigreh iugreiuhgreiu griughreiugh eriughriug";
	shop_products[1].price = 900.99;
	shop_products[1].rating = 4.5;
	shop_products[1].onsale = true;
	shop_products[1].name = "This is a great product";
	shop_products[1].description = "This is the product desctription.   fijg ihgifdhgis griefirehfuiregei rugiruigreh iugreiuhgreiu griughreiugh eriughriug";
	shop_products[2].price = 192.99;
	shop_products[2].rating = 5;
	shop_products[2].onsale = true;
	shop_products[2].name = "This  a product";
	shop_products[2].description = "This is the  .  ghivbfdigsfji fijg ihgifdhgis griefirehfuiregei rugiruigreh iugreiuhgreiu griughreiugh eriughriug";
	shop_products[3].price = 239.00;
	shop_products[3].rating = 1.2;
	shop_products[3].onsale = false;
	shop_products[3].name = "This is a ";
	shop_products[3].description = "This is the  desctription. dhuisahisfhsdifhdsuifdsifsdi ghivbfdigsfji fijg ihgifdhgis griefirehfuiregei rugiruigreh iugreiuhgreiu griughreiugh ";
	shop_products[4].price = 0.99;
	shop_products[4].rating = 2.7;
	shop_products[4].onsale = false;
	shop_products[4].name = "This is a product";
	shop_products[4].description = "This is the product desctription.  ghivbfdigsfji    rugiruigreh iugreiuhgreiu griughreiugh eriughriug";
	shop_products[5].price = 0.0;
	shop_products[5].rating = 1.1;
	shop_products[5].onsale = true;
	shop_products[5].name = "This is a product atdsad";
	shop_products[5].description = "This is the  desctription. dhuisahisfhsdifhdsuifdsifsdi ghivbfdigsfji fijg   rugiruigreh iugreiuhgreiu griughreiugh ";
	shop_products[6].price = 2.99;
	shop_products[6].rating = 4.3;
	shop_products[6].onsale = false;
	shop_products[6].name = "This is jfsduihfosl a product";
	shop_products[6].description = "This is the  .  ghivbfdigsfji fijg ihgifdhgis griefirehfuiregei rugiruigreh iugreiuhgreiu griughreiugh eriughriug";

	int shop_amountofproducts = 7;
	int shop_productindex = 0;
	int shop_spaceabovelist = 3;//4;
	int shop_pagenumber = 1;
	int shop_maxpagenumber = 1;

	initscr();			/* Start curses mode			*/
	raw();				/* Line buffering disabled		*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..			*/
	noecho();			/* Don't echo() while we do getch	*/
	getmaxyx(stdscr,row,col);	/* get the number of rows and columns	*/

	if (has_colors()) { /* bleh i both love and hate this implementation of color managment but i mean whatever ig */
		start_color();
		use_default_colors();
		init_pair(TAB_COLOR, COLOR_YELLOW, DEFAULT_COLOR);
		init_pair(TAB_TEXT, COLOR_WHITE, DEFAULT_COLOR);
		init_pair(TAB_TEXT_HIGH, COLOR_WHITE, COLOR_RED);
		init_pair(SHOP_INDEX, COLOR_RED, DEFAULT_COLOR);
		init_pair(SHOP_NAME, COLOR_WHITE, DEFAULT_COLOR);
		init_pair(SHOP_SHORT_DESC, COLOR_BLUE, DEFAULT_COLOR);
		init_pair(SHOP_PRICE, COLOR_MAGENTA, DEFAULT_COLOR);
		init_pair(SHOP_STAR_ON, COLOR_YELLOW, DEFAULT_COLOR);
		init_pair(SHOP_STAR_OFF, COLOR_RED, DEFAULT_COLOR);
		init_pair(SHOP_ON_SALE, COLOR_GREEN, DEFAULT_COLOR);
		init_pair(SHOP_INFO, COLOR_CYAN, DEFAULT_COLOR);
	}

	while (running) {
		erase();

		if (typing) { /* show what ur currently typing */
			mvaddch(row-1, 0, ':');
			printw("%-*.*s", col-2, col-2, typingbuffer);
		}

		attron(COLOR_PAIR(TAB_COLOR));
		//mvhline(0, 0, ACS_HLINE, col);
		//mvhline(2, 0, ACS_HLINE, col);
		mvhline(1, 0, ACS_HLINE, col);
		attroff(COLOR_PAIR(TAB_COLOR));

		for (int i = 0; i <= amountoftabs; i++) { /* wish i could make it smaller but this draws the tabs */
			int position = (int)((float)i*(float)col/(float)amountoftabs);

			//int textcolor = i == tab ? TAB_TEXT_HIGH : TAB_TEXT;
			if (i == tab) {
				attron(A_REVERSE);// | A_BOLD);
			}
			attron(COLOR_PAIR(TAB_TEXT));
			//mvprintw(1, position+1, tabs[i]);
			mvprintw(0, position+1, tabs[i]);
			attroff(COLOR_PAIR(TAB_TEXT));
			attroff(A_REVERSE);// | A_BOLD);

			attron(COLOR_PAIR(TAB_COLOR));
			//mvaddch(0, position  , ACS_ULCORNER);
			//mvaddch(0, position-1, ACS_URCORNER);
			//mvaddch(1, position  , ACS_VLINE);
			mvaddch(0, position  , ACS_VLINE);
			//mvaddch(1, position-1, ACS_VLINE);
			//mvaddch(2, position  , ACS_BTEE);
			//mvaddch(1, position  , ACS_BTEE);
			//mvaddch(2, position-1, ACS_BTEE);
			attroff(COLOR_PAIR(TAB_COLOR));
		}

		switch (tab) { /* tab spesific drawing */
			case 0:
				attron(COLOR_PAIR(SHOP_INFO));
				mvprintw(shop_spaceabovelist-1, 0, "Page [%d/%d] showing %d product(s)", shop_pagenumber, shop_maxpagenumber, shop_amountofproducts);
				attron(COLOR_PAIR(SHOP_INFO));

				for (int i = 0; i < shop_amountofproducts; i++) {
					if (i == shop_productindex) {
						attron(A_REVERSE);// | A_BOLD);
					}

					int pricelength = (int)log10f(max(1, shop_products[i].price));

					attron(COLOR_PAIR(SHOP_INDEX));
					mvprintw(i+shop_spaceabovelist, 0, "%02d ", i+1);
					attroff(COLOR_PAIR(SHOP_INDEX));

					attron(COLOR_PAIR(SHOP_NAME));
					//mvhline(i*2+3, 3, '-', col-8);
					//mvprintw(i*2+shop_spaceabovelist, 3, "%-*.*s", col-10, col-10, shop_products[i].name);
					int namelength = round(((float)col-18)/4);
					mvprintw(i+shop_spaceabovelist, 3, "%-*.*s ", namelength, namelength, shop_products[i].name);
					attroff(COLOR_PAIR(SHOP_NAME));
					
					attron(COLOR_PAIR(SHOP_SHORT_DESC));
					//mvprintw(i*2+1+shop_spaceabovelist, 0, "%-*.*s", col-7, col-7, shop_products[i].description);
					int desclength = round(((float)col-17)/4*3)-pricelength-1;
					mvprintw(i+shop_spaceabovelist, namelength+4, "%-*.*s ", desclength, desclength, shop_products[i].description);
					attroff(COLOR_PAIR(SHOP_SHORT_DESC));

					attron(COLOR_PAIR(SHOP_PRICE));
					//mvprintw(i*2+shop_spaceabovelist, col-(int)log10f(max(1, shop_products[i].price))-7, " $%2.2f", shop_products[i].price);
					mvprintw(i+shop_spaceabovelist, col-pricelength-13, "$%2.2f ", shop_products[i].price);
					attroff(COLOR_PAIR(SHOP_PRICE));
					
					if (shop_products[i].onsale) {
						attron(COLOR_PAIR(SHOP_ON_SALE));
						//mvaddch(i*2+shop_spaceabovelist, col-1, ACS_DARROW);
						mvaddch(i+shop_spaceabovelist, col-8, ACS_DARROW);
						attroff(COLOR_PAIR(SHOP_ON_SALE));
					}
					
					attroff(A_REVERSE);// | A_BOLD);

					for (int j = 1; j < 6; j++) {
						if (j <= (int)shop_products[i].rating)
							attron(COLOR_PAIR(SHOP_STAR_ON));
						else
							attron(COLOR_PAIR(SHOP_STAR_OFF));

						if (j <= (int)(shop_products[i].rating + 0.5))
							//mvaddch(i*2+1+shop_spaceabovelist, col-7+j, ACS_DIAMOND);
							mvaddch(i+shop_spaceabovelist, col-7+j, ACS_DIAMOND);
						else
							//mvaddch(i*2+1+shop_spaceabovelist, col-7+j, ACS_BULLET);
							mvaddch(i+shop_spaceabovelist, col-7+j, ACS_BULLET);

						attroff(COLOR_PAIR(SHOP_STAR_ON));
						attroff(COLOR_PAIR(SHOP_STAR_OFF));
					}
				}
				break;
		}

		move(row-1, min(col-1, typing ? pointer + 1 : 0));
		ch = getch();


		if (ch == KEY_RESIZE) { /* resize takes top priority over all the other ones */
			getmaxyx(stdscr,row,col);
		} else if (typing) { /* giant block of spagetti for global typing buffer */
			if (ch >= ' ' && ch <= '~')
				insertChar(typingbuffer, ch, pointer++);
			else switch(ch) {
				case KEY_BACKSPACE:
					if (pointer > 0)
						rmChar(typingbuffer, --pointer);
					break;
				case KEY_RIGHT:
					if (pointer < strlen(typingbuffer))
						pointer++;
					break;
				case KEY_LEFT:
					if (pointer > 0)
						pointer--;
					break;
				case 3:
					typing = false;
					typingbuffer[0] = '\0';
					pointer = 0;
					break;
			}
		} else switch (ch) { /* ugly switch case for global keybinds */
			case 's':
				tab = 0;
				break;
			case 'c':
				tab = 1;
				break;
			case 'o':
				tab = 2;
				break;
			case 'e':
				tab = 3;
				break;
			case 9:
				if (tab < amountoftabs-1)
					tab++;
				break;
			case 353: /* for some fucking reason 353 is SHIFT-TAB no clue why */
				if (tab > 0)
					tab--;
				break;
			case 'q':
				running = false;
				break;
			case KEY_F(1):
				printw("F1 Key pressed");
				break;
			default:
				switch (tab) { /* switch case for all the tab spesific keybinds */
					case 0:
						switch (ch) {
							case 'f':
								typing = true;
								break;
							case KEY_DOWN:
								shop_productindex = min(shop_amountofproducts-1, shop_productindex+1);
								break;
							case KEY_UP:
								shop_productindex = max(0, shop_productindex-1);
								break;
						}
						break;
				}
		}
	}

	endwin();			/* End curses mode			*/

	return 0;
}
