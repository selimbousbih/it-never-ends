#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

typedef struct Menu
{
	int etat;
	int done, getInput;
	int continuer;
	int opt1_select, opt2_select;
	int SHOW_EXIT, SHOW_OPTION;
	int exit_yes, exit_no;
	int intro;
    int continue_level;
    int fullscreenfix;

}Menu;


#endif // MENU_H_INCLUDED
