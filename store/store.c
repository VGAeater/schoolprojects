#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "client.h"

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
#define SHOP_INCART 29


//struct product {
//	unsigned int *amountincart;
//	unsigned int amountofoptions;
//	unsigned int id;
//	float *price;
//	float rating;
//	bool onsale;
//	char *name;
//	char *description;
//	char *shortdesc;
//	char **options;
//};

int main() {
	int ch, row, col;
	int tab = 0;
	bool running = true;

	char typingbuffer[256] = "";
	int pointer = 0;
	bool typing = false;

	char* tabs[4] = { "[S]hop", "[C]art", "[O]rder", "S[e]rver" };

	int amountoftabs = 4;

	struct product shop_products[100]; /* im not making a pointer to an array of structs because kms no */
	shop_products[0].id = 0;
	shop_products[0].price = malloc(3*sizeof(float));
	shop_products[0].price[0] = 9.99;
	shop_products[0].price[1] = 9.99;
	shop_products[0].price[2] = 9.99;
	shop_products[0].rating = 4.5;
	shop_products[0].onsale = false;
	shop_products[0].name = "Standing desks";
	shop_products[0].description = "the best standing desks on this side of the intergalactic supercluster";
	shop_products[0].shortdesc = "High quality desks lol";
	shop_products[0].options = malloc(3*sizeof(char*));
	shop_products[0].options[0] = "Small";
	shop_products[0].options[1] = "Medium";
	shop_products[0].options[2] = "Large";
	shop_products[0].amountincart = malloc(3*sizeof(int));
	shop_products[0].amountincart[0] = 0;
	shop_products[0].amountincart[1] = 0;
	shop_products[0].amountincart[2] = 0;
	shop_products[0].amountofoptions = 3;


	int shop_amountofproducts = 1;
	int shop_productindex = 0;
	int shop_productdisplayindex = 0;
	int shop_spaceabovelist = 3;
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
		init_pair(SHOP_NAME, COLOR_GREEN, DEFAULT_COLOR);
		init_pair(SHOP_SHORT_DESC, COLOR_BLUE, DEFAULT_COLOR);
		init_pair(SHOP_PRICE, COLOR_MAGENTA, DEFAULT_COLOR);
		init_pair(SHOP_STAR_ON, COLOR_YELLOW, DEFAULT_COLOR);
		init_pair(SHOP_STAR_OFF, COLOR_RED, DEFAULT_COLOR);
		init_pair(SHOP_ON_SALE, COLOR_GREEN, DEFAULT_COLOR);
		init_pair(SHOP_INFO, COLOR_CYAN, DEFAULT_COLOR);
		init_pair(SHOP_INCART, COLOR_MAGENTA, DEFAULT_COLOR);
	}

	while (running) {
		erase();

		if (typing) { /* show what ur currently typing */
			mvaddch(row-1, 0, ':');
			printw("%-*.*s", col-2, col-2, &typingbuffer[max(0,strlen(typingbuffer)-col+2)]);
		}

		attron(COLOR_PAIR(TAB_COLOR));
		mvhline(1, 0, ACS_HLINE, col);
		attroff(COLOR_PAIR(TAB_COLOR));

		for (int i = 0; i <= amountoftabs; i++) { /* wish i could make it smaller but this draws the tabs */
			int position = (int)((float)i*(float)col/(float)amountoftabs);
			int length = (int)((float)(i+1)*(float)col/(float)amountoftabs)-position-1;

			if (i == tab)
				attron(A_REVERSE);

			attron(COLOR_PAIR(TAB_TEXT));
			mvprintw(0, position+1, "%-*.*s", length, length, tabs[i]);
			attroff(COLOR_PAIR(TAB_TEXT));

			attroff(A_REVERSE);

			attron(COLOR_PAIR(TAB_COLOR));
			mvaddch(0, position, ACS_VLINE);
			attroff(COLOR_PAIR(TAB_COLOR));
		}

		switch (tab) { /* tab spesific drawing */
			case 0:
				attron(COLOR_PAIR(SHOP_INFO));
				mvprintw(shop_spaceabovelist-1, 0, "Page [%d/%d] showing %d product(s)", shop_pagenumber, shop_maxpagenumber, shop_amountofproducts);
				attron(COLOR_PAIR(SHOP_INFO));

				int amountofproductsdisplayed = min(row-shop_spaceabovelist-1, shop_amountofproducts);
				for (int i = 0; i < amountofproductsdisplayed; i++) {
					if (i == shop_productindex)
						attron(A_REVERSE);

					int pricelength = (int)log10f(max(1, shop_products[i].price[0]));

					attron(COLOR_PAIR(SHOP_INDEX));
					mvprintw(i+shop_spaceabovelist, 0, "%02d ", i);
					attroff(COLOR_PAIR(SHOP_INDEX));

					int namelength = round(((float)col-19)/4);
					attron(COLOR_PAIR(SHOP_NAME));
					mvprintw(i+shop_spaceabovelist, 3, "%-*.*s ", namelength, namelength, shop_products[i].name);
					attroff(COLOR_PAIR(SHOP_NAME));

					int desclength = round(((float)col-18)/4*3)-pricelength-1;
					attron(COLOR_PAIR(SHOP_SHORT_DESC));
					mvprintw(i+shop_spaceabovelist, namelength+4, "%-*.*s ", desclength, desclength, shop_products[i].shortdesc);
					attroff(COLOR_PAIR(SHOP_SHORT_DESC));

					attron(COLOR_PAIR(SHOP_PRICE));
					mvprintw(i+shop_spaceabovelist, col-pricelength-14, "$%2.2f ", shop_products[i].price[0]);
					attroff(COLOR_PAIR(SHOP_PRICE));
					
					if (shop_products[i].onsale) {
						attron(COLOR_PAIR(SHOP_ON_SALE));
						mvaddch(i+shop_spaceabovelist, col-9, ACS_DARROW);
						attroff(COLOR_PAIR(SHOP_ON_SALE));
					}

					attroff(A_REVERSE);

					if (i == shop_productindex)
						attron(A_BOLD);

					for (int j = 1; j < 6; j++) {
						attron(COLOR_PAIR(j <= (int)shop_products[i].rating ? SHOP_STAR_ON : SHOP_STAR_OFF));
						mvaddch(i+shop_spaceabovelist, col-8+j, j <= (int)(shop_products[i].rating + 0.5) ? ACS_DIAMOND : ACS_BULLET);
						attroff(COLOR_PAIR(SHOP_STAR_OFF));

						//attron(COLOR_PAIR(SHOP_STAR_ON));
						//mvprintw(i+shop_spaceabovelist, col-2, "%1d", (int)(shop_products[i].rating*10)%10);
						//attroff(COLOR_PAIR(SHOP_STAR_ON));
					}

					attron(COLOR_PAIR(SHOP_INCART));
					mvaddch(i+shop_spaceabovelist, col-1, shop_products[i].amountincart ? ACS_STERLING : ACS_BULLET);
					attroff(COLOR_PAIR(SHOP_INCART));

					attroff(A_BOLD);
				}
				break;
		}

		move(row-1, min(col-1, typing ? pointer + 1 : 0));
		ch = getch();


		if (ch == KEY_RESIZE) /* resize takes top priority over all the other ones */
			getmaxyx(stdscr,row,col);
		else if (typing) { /* giant block of spagetti for global typing buffer */
			if (ch >= ' ' && ch <= '~') {
				if (strlen(typingbuffer) < 255) /* max length 255 cuz the last char has to be \0 */
					insertChar(typingbuffer, ch, pointer++);
			} else switch(ch) {
				case KEY_BACKSPACE: if (pointer > 0) rmChar(typingbuffer, --pointer); break;	// backspace
				case KEY_RIGHT: if (pointer < strlen(typingbuffer)) pointer++; break;		// move right
				case KEY_LEFT: if (pointer > 0) pointer--; break;				// move left
				case 3:
					typing = false;
					typingbuffer[0] = '\0'; // delete whole buffer with O(1) <-- kinda cool how cstrings work
					pointer = 0;
					break;
			}
		} else switch (ch) { /* ugly switch case for global keybinds */
			case 's': tab = 0; break;					// go to shop
			case 'c': tab = 1; break;					// go to cart
			case 'o': tab = 2; break;					// go to order tab
			case 'e': tab = 3; break;					// go to servers tab
			case   9: tab = tab < amountoftabs-1 ? tab+1 : 0; break;	// move tab forward
			case 353: tab = tab > 0 ? tab-1 : amountoftabs-1; break;	// move tab backward /* for some fucking reason 353 is SHIFT-TAB no clue why */
			case 'q': running = false; break;				// leave
			/*case KEY_F(1):
				printw("F1 Key pressed");
				break;*/
			default:
				switch (tab) { /* switch case for all the tab spesific keybinds */
					case 0:
						switch (ch) {
							case 'f': typing = true; break;
							case KEY_DOWN:
								shop_productindex++;
								if (shop_productindex > shop_amountofproducts-1)
									shop_productindex = shop_amountofproducts-1;//0;
								// HEY FUTURE STRATTON MAKE THE LINES FOLLOW THE CURSOR IF TOO MANY ENTRYS imma go make backend now lol
								break;
							case KEY_UP:
								shop_productindex--;
								if (shop_productindex < 0)
									shop_productindex = 0;//shop_amountofproducts-1;
								break;
						}
						break;
				}
		}
	}

	endwin();			/* End curses mode			*/

	return 0;
}
