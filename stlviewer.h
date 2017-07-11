#include <gtk/gtk.h>
#include <stdio.h>


int sx,sy;
int x, y,xold=0,yold=0;
 
float xdiff = 0.0f;
float ydiff = 0.0f;
char mode='r';

/*VariablesDeclarations*/
const gchar *filename="Heart.stl";
char title[] = "STL Viewer";

GtkWidget *window;
GtkWidget *da;
GtkWidget *parentVbox;
GtkWidget *tool;
GdkGLConfig *glconfig;
GtkWidget *vbox;

GtkWidget *menu_bar;
GtkWidget *menu_item_file;
GtkWidget *menu_file;
GtkWidget *menu_item_new;
GtkWidget *menu_item_open;
GtkWidget *menu_item_save;
GtkWidget *menu_item_saveas;
GtkWidget *menu_item_quit;

GtkWidget *menu_item_edit;
GtkWidget *menu_edit;
GtkWidget *menu_item_undo;
GtkWidget *menu_item_redo;
GtkWidget *menu_item_preferences;

GtkWidget *menu_item_view;
GtkWidget *menu_view;
GtkWidget *menu_item_zoomin;
GtkWidget *menu_item_zoomout;
GtkWidget *menu_item_fit;

GtkWidget *tool_bar;
GtkWidget *button_new;
GtkWidget *button_open;
GtkWidget *button_save;
GtkWidget *button_saveas;
GtkWidget *button_quit;	

GtkWidget *button_undo;
GtkWidget *button_redo;

GtkWidget *button_zoomin;	
GtkWidget *button_zoomout;	
GtkWidget *button_fit;	
GtkWidget *button_rotate;	
GtkWidget *button_move;	
    
GtkWidget *open_file_dlg;
GtkWidget *open_file_dlg_ok;
GtkWidget *open_file_dlg_cancel;
GtkWidget *saveas_file_dlg;
GtkWidget *saveas_file_dlg_ok;
GtkWidget *saveas_file_dlg_cancel;

/*CallBacksFunctions*/
/*MenuBarCallBacks*/
void menu_item_new_activated(GtkWidget*,gpointer);
void menu_item_open_activated(GtkWidget*,gpointer);
void menu_item_save_activated(GtkWidget*,gpointer);
void menu_item_saveas_activated(GtkWidget*,gpointer);
void menu_item_quit_activated(GtkWidget*,gpointer);
void menu_item_undo_activated(GtkWidget*,gpointer);
void menu_item_redo_activated(GtkWidget*,gpointer);
void menu_item_preferences_activated(GtkWidget*,gpointer);
void menu_item_zoomin_activated(GtkWidget*,gpointer);
void menu_item_zoomout_activated(GtkWidget*,gpointer);
void menu_item_fit_activated(GtkWidget*,gpointer);
/*ToolBarCallBacks*/
void button_new_clicked(GtkWidget*,gpointer);
void button_open_clicked(GtkWidget*,gpointer);
void button_save_clicked(GtkWidget*,gpointer);
void button_saveas_clicked(GtkWidget*,gpointer);
void button_undo_clicked(GtkWidget*,gpointer);
void button_redo_clicked(GtkWidget*,gpointer);
void button_zoomin_clicked(GtkWidget*,gpointer);
void button_zoomout_clicked(GtkWidget*,gpointer);
void button_fit_clicked(GtkWidget*,gpointer);
void button_rotate_clicked(GtkWidget*,gpointer);
void button_move_clicked(GtkWidget*,gpointer);
/*OpenFileDialogCallBacks*/
void open_file_dlg_ok_clicked(GtkWidget*,gpointer);
void open_file_dlg_cancel_clicked(GtkWidget*,gpointer);
/*SaveAsFileDialogCallBacks*/
void saveas_file_dlg_ok_clicked(GtkWidget*,gpointer);
void saveas_file_dlg_cancel_clicked(GtkWidget*,gpointer);

/*Functions*/
void menus_tools();
void signals();

/*EditFunctions*/
void edit_new(void);
void edit_open(void);
void edit_save(void);
void edit_saveas(void);
void edit_close(void);
void edit_quit(void);
void edit_undo(void);
void edit_redo(void);
void edit_preferences(void);
void edit_zoomin(void);
void edit_zoomout(void);
void edit_fit(void);
