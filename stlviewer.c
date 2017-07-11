/*sudo apt-get install libgtk-3-dev

sudo apt-get install libgtkglext1-dev
* */


/* Compile with:
 *    gcc -o stlviewer `pkg-config --cflags --libs gtk+-2.0 gtkglext-1.0 gtkglext-x11-1.0` -lgraph stlviewer.c
 */

#include <gtk/gtk.h>
#include <gtk/gtkgl.h>
#include <GL/gl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "declare.h"

#define ALPHA 0.5
//#pragma comment(lib,"opengl32.lib")

static float ang = 30.;
int flag=0;

static gboolean button_press_event( GtkWidget *widget, GdkEventButton *event ) 
{
	if (event->button == 1 ) 
	{
	  sx=(int)event->x-550;
	  sy=-((int)event->y-350-55);
	  
	  //printf("but down  %i , %i\n", sx,sy);
      xold=0;
      yold=0;
    }  

	return TRUE;
}

static gboolean motion_notify_event( GtkWidget *widget, GdkEventMotion *event ) {

	int xr,yr;
	GdkModifierType state;
	gdk_window_get_pointer (window->window, &xr, &yr, &state);
	
	if (state & GDK_BUTTON1_MASK) 
	{	
		//printf(" %i , %i \n", xold, yold);
		x=x+xr-550-sx-xold;
		y= y-(yr-350)-sy+110-yold;	
		xold=xr-550-sx;
		yold=-(yr-350)-sy+110;			
	}

	return TRUE;
}

void axis()
{
	glBegin (GL_LINES);
	glColor3f (1., 0., 0.);
	glVertex3f (0., 0., 0.);
	glVertex3f (50., 0., 0.);
	glEnd ();
	
	glBegin (GL_LINES);//x
	glVertex3f (55., 5., 0.);
	glVertex3f (60., -5., 0.);
	glEnd ();
	
	glBegin (GL_LINES);
	glVertex3f (55., -5., 0.);
	glVertex3f (60., 5., 0.);
	glEnd ();
	
	
	
	glBegin (GL_LINES);
	glColor3f (0., 1., 0.);
	glVertex3f (0., 0., 0.);
	glVertex3f (0., 50., 0.);
	glEnd ();
	
	glBegin (GL_LINES);//y
	glVertex3f (0., 55., 5.);
	glVertex3f (0., 57.5, 0.);
	glEnd ();
	
	glBegin (GL_LINES);
	glVertex3f (0., 55., -5.);
	glVertex3f (0., 60., 5.);
	glEnd ();
	
	glBegin (GL_LINES);
	glColor3f (0., 0., 1.);
	glVertex3f (0., 0., 0.);
	glVertex3f (0., 0., 50.);
	glEnd ();
	
	glBegin (GL_LINE_STRIP);//z
	glVertex3f (-2.5, 0., 65.);
	glVertex3f (2.5, 0., 65.);
	glVertex3f (-2.5, 0., 55.);
	glVertex3f (2.5, 0., 55.);
	glEnd ();
	
}	


void draw()
{    
	 float p,q,r,x,y,z;
	 FILE *fp;
     char buff[255];
     fp = fopen(filename, "r");
	 glBegin(GL_TRIANGLES);
	 if(!fp)
	    return;
     while(!feof(fp))  
     {
		 fscanf(fp, "%s", buff);
		 //printf("%s\n", buff );
		 if(strcmp(buff,"solid") == 0) 
		 {
		   if(flag==0)
		   {
		   fscanf(fp, "%s", buff);
		   printf("%s.stl\n", buff );
		   flag=1;
	       }
		   //continue;
	     }
		 if(strcmp(buff,"normal") == 0) 
		 { 
		   fscanf(fp, "%s", buff);
           p=atof(buff);
           fscanf(fp, "%s", buff);
           q=atof(buff);
           fscanf(fp, "%s", buff);
           r=atof(buff);
		   //continue;
		 }  
		 //if(buff=="vertex")  
		 if(strcmp(buff,"vertex") == 0)
		 {
           fscanf(fp, "%s", buff);
           x=atof(buff);
           fscanf(fp, "%s", buff);
           y=atof(buff);
           fscanf(fp, "%s", buff);
           z=atof(buff);
           //printf("x: %f  y:%f  z:%f\n",x,y,z);
           glNormal3f(p,q,r);
           glVertex3f(x,y,z);
	     }
     }
     glEnd();
     fclose(fp);
}

static gboolean expose (GtkWidget *da, GdkEventExpose *event, gpointer user_data)
{
	GdkGLContext *glcontext = gtk_widget_get_gl_context (da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (da);

	// g_print (" :: expose\n");

	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
	{
		g_assert_not_reached ();
	}

	/* draw in here */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//ang=90;
	
	glPushMatrix();
	glTranslatef(-500,-300,0.0);
	if(mode=='r')
	{
	  glRotatef(-y, 1.0f, 0.0f, 0.0f);
      glRotatef(x, 0.0f, 1.0f, 0.0f);
      //glRotatef (ang, 1, 1, 1);
    }  
	axis();
	glPopMatrix ();
	
	glPushMatrix();
	
	if(mode=='m')
	{
	  glTranslatef(x,y,0.0); 
    }
	else 
	{
	  glRotatef(-y, 1.0f, 0.0f, 0.0f);
      glRotatef(x, 0.0f, 1.0f, 0.0f);
      //glRotatef (ang, 1, 1, 1);
    } 
	glColor3d(1,1,1);
    glTranslatef(-204,-250,-25.0);
    glScalef (4, 4, 4);
	/*glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)

	glEnable(GL_COLOR_MATERIAL);
  
      glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);*/
    
     
     static GLfloat pos[4] = {0,0,1,0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);
	static float ambientlys[] = {0.4,0.4,0.4,1};
	static float diffuselys[] = {0.6,0.6,0.6,1};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientlys);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuselys);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	//glClearDepth(1.0f);	
	//glEnable(GL_LIGHT1);
	glDepthFunc(GL_LEQUAL);	
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0,0,0,0.5);
	glEnable(GL_NORMALIZE);
     
     
    //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); 
    draw();
    
	glPopMatrix ();

	if (gdk_gl_drawable_is_double_buffered (gldrawable))
		gdk_gl_drawable_swap_buffers (gldrawable);

	else
		glFlush ();

	gdk_gl_drawable_gl_end (gldrawable);

	return 1;
}

static gboolean configure (GtkWidget *da, GdkEventConfigure *event, gpointer user_data)
{
	GdkGLContext *glcontext = gtk_widget_get_gl_context (da);
	GdkGLDrawable *gldrawable = gtk_widget_get_gl_drawable (da);

	if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
	{
		g_assert_not_reached ();
	}

	glLoadIdentity();
	glViewport (0, 0, da->allocation.width, da->allocation.height);
	glOrtho (-550,550,-350,350,-20050,10000);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//glMatrixMode(GL_PROJECTION);
	
    //glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); 
	
	gdk_gl_drawable_gl_end (gldrawable);

	return 1;
}

static gboolean rotate (gpointer user_data)
{
	GtkWidget *da = GTK_WIDGET (user_data);

	ang++;

	gdk_window_invalidate_rect (da->window, &da->allocation, 0);
	gdk_window_process_updates (da->window, 0);

	return 1;
}

/*TheCallBackFunctions*/
void menu_item_new_activated(GtkWidget *widget,gpointer data)
{
  edit_new();
}
void menu_item_open_activated(GtkWidget *widget,gpointer data)
{
  edit_open();
}
void menu_item_save_activated(GtkWidget *widget,gpointer data)
{
  edit_save();
}
void menu_item_saveas_activated(GtkWidget *widget,gpointer data)
{
  edit_saveas();
}
void menu_item_quit_activated(GtkWidget *widget,gpointer data)
{
  edit_quit();
}
void menu_item_undo_activated(GtkWidget *widget,gpointer data)
{
  edit_undo();
}
void menu_item_redo_activated(GtkWidget *widget,gpointer data)
{
  edit_redo();
}
void menu_item_zoomin_activated(GtkWidget *widget,gpointer data)
{
  edit_zoomin();
}
void menu_item_zoomout_activated(GtkWidget *widget,gpointer data)
{
  edit_zoomout();
}
void menu_item_fit_activated(GtkWidget *widget,gpointer data)
{
  edit_fit();
}


void button_new_clicked(GtkWidget *widget,gpointer data)
{
  edit_new();
}
void button_open_clicked(GtkWidget *widget,gpointer data)
{
  edit_open();
}
void button_save_clicked(GtkWidget *widget,gpointer data)
{
  edit_save();
}
void button_saveas_clicked(GtkWidget *widget,gpointer data)
{
  edit_saveas();
}
void button_undo_clicked(GtkWidget *widget,gpointer data)
{
  edit_undo();
}
void button_redo_clicked(GtkWidget *widget,gpointer data)
{
  edit_redo();
}
void button_zoomin_clicked(GtkWidget *widget,gpointer data)
{
  edit_zoomin();
}
void button_zoomout_clicked(GtkWidget *widget,gpointer data)
{
  edit_zoomout();
}
void button_fit_clicked(GtkWidget *widget,gpointer data)
{
  edit_fit();
}

void button_rotate_clicked(GtkWidget *widget,gpointer data)
{
  if(mode=='r')
     mode='m';
  else
     mode='r';  
  x=0;
  y=0;    
}

void open_file_dlg_ok_clicked(GtkWidget *widget,gpointer data)
{
  int bytes_read;
  FILE *fp;
  filename=gtk_file_selection_get_filename(GTK_FILE_SELECTION(open_file_dlg));
  if((fp=fopen(filename,"r"))==NULL)
  {
    exit(1);
  }

  fclose(fp);
  gtk_widget_destroy(open_file_dlg);
}
void open_file_dlg_cancel_clicked(GtkWidget *widget,gpointer data)
{
  gtk_widget_destroy(open_file_dlg);
}
void saveas_file_dlg_ok_clicked(GtkWidget *widget,gpointer data)
{
  FILE *fp;
  filename=gtk_file_selection_get_filename(GTK_FILE_SELECTION(saveas_file_dlg));
  fp=fopen(filename,"w");
  if(!fp)
  {
   return;
  }
  fclose(fp);
  gtk_widget_destroy(saveas_file_dlg);
}
void saveas_file_dlg_cancel_clicked(GtkWidget *widget,gpointer data)
{
  gtk_widget_destroy(saveas_file_dlg);
}
/*TheTextEditFunctions*/
void edit_new()
{
  edit_close();
}
void edit_open()
{
  /*FirstCloseTheOpennedFile*/
  edit_close();
  /*CreateTheOpenFileDialog*/
  open_file_dlg=gtk_file_selection_new("OpenFile...");
  open_file_dlg_ok=GTK_FILE_SELECTION(open_file_dlg)->ok_button;
  open_file_dlg_cancel=GTK_FILE_SELECTION(open_file_dlg)->cancel_button;
  /*OpenFileDialogClickedSignals*/
  g_signal_connect(G_OBJECT(open_file_dlg_ok),"clicked",G_CALLBACK(open_file_dlg_ok_clicked),NULL);
  g_signal_connect(G_OBJECT(open_file_dlg_cancel),"clicked",G_CALLBACK(open_file_dlg_cancel_clicked),NULL);
  gtk_widget_show_all(open_file_dlg);
}
void edit_save()
{
  if(filename==NULL)
  {
    edit_saveas();
  }
  else
  {
    FILE *fp;
    fp=fopen(filename,"w");
    if(!fp)
    {
      return;
    }
    fclose(fp);
  }
}
void edit_saveas()
{
  /*CreateTheSaveAsFileDialog*/
  saveas_file_dlg=gtk_file_selection_new("SaveFileAs...");
  saveas_file_dlg_ok=GTK_FILE_SELECTION(saveas_file_dlg)->ok_button;
  saveas_file_dlg_cancel=GTK_FILE_SELECTION(saveas_file_dlg)->cancel_button;
  /*SaveAsFileDialogClickedSignals*/
  g_signal_connect(G_OBJECT(saveas_file_dlg_ok),"clicked",G_CALLBACK(saveas_file_dlg_ok_clicked),NULL); 
  g_signal_connect(G_OBJECT(saveas_file_dlg_cancel),"clicked",G_CALLBACK(saveas_file_dlg_cancel_clicked),NULL);
  gtk_widget_show_all(saveas_file_dlg);
}
void edit_close()
{
}
void edit_quit()
{
  exit(0);
}
void edit_undo()
{
  
}
void edit_redo()
{
  
}
void edit_preferences()
{
	
}
void edit_zoomin()
{
  
}
void edit_zoomout()
{
  
}
void edit_fit()
{
  
}

void menus_tools()
{
	/*CreateTheMenuBar&AttachItToTheVBox*/
    menu_bar=gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);
    menu_item_file=gtk_menu_item_new_with_mnemonic("File");
    gtk_container_add(GTK_CONTAINER(menu_bar),menu_item_file);
    menu_file=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_file),menu_file);
    menu_item_new=gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
    gtk_container_add(GTK_CONTAINER(menu_file),menu_item_new);
    menu_item_open=gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
    gtk_container_add(GTK_CONTAINER(menu_file),menu_item_open);
    menu_item_save=gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE,NULL);
    gtk_container_add(GTK_CONTAINER(menu_file),menu_item_save);
    menu_item_saveas=gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE_AS,NULL);
    gtk_container_add(GTK_CONTAINER(menu_file),menu_item_saveas);
    menu_item_quit=gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,NULL);
    gtk_container_add(GTK_CONTAINER(menu_file),menu_item_quit);
    
    menu_item_edit=gtk_menu_item_new_with_mnemonic("Edit");
    gtk_container_add(GTK_CONTAINER(menu_bar),menu_item_edit);
    menu_edit=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_edit),menu_edit);
    menu_item_undo=gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO,NULL);
    gtk_container_add(GTK_CONTAINER(menu_edit),menu_item_undo);
    menu_item_redo=gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO,NULL);
    gtk_container_add(GTK_CONTAINER(menu_edit),menu_item_redo);
    menu_item_preferences=gtk_image_menu_item_new_from_stock(GTK_STOCK_PREFERENCES,NULL);
    gtk_container_add(GTK_CONTAINER(menu_edit),menu_item_preferences);
    
    menu_item_view=gtk_menu_item_new_with_mnemonic("View");
    gtk_container_add(GTK_CONTAINER(menu_bar),menu_item_view);
    menu_view=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item_view),menu_view);
    menu_item_zoomin=gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_IN,NULL);
    gtk_container_add(GTK_CONTAINER(menu_view),menu_item_zoomin);
    menu_item_zoomout=gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_OUT,NULL);
    gtk_container_add(GTK_CONTAINER(menu_view),menu_item_zoomout);
    menu_item_fit=gtk_image_menu_item_new_from_stock(GTK_STOCK_ZOOM_FIT,NULL);
    gtk_container_add(GTK_CONTAINER(menu_view),menu_item_fit);
    
    /*CreateTheToolBar&AttachItToTheVBox*/
    tool_bar=gtk_toolbar_new();
    gtk_box_pack_start(GTK_BOX(vbox),tool_bar,0,0,0);
    gtk_toolbar_set_style(GTK_TOOLBAR(tool_bar),GTK_TOOLBAR_BOTH);
    button_new=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_NEW,"NewFile",NULL,NULL,NULL,-1);
    button_open=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_OPEN,"OpenFile",NULL,NULL,NULL,-1);
    button_save=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_SAVE,"SaveFile",NULL,NULL,NULL,-1);
    button_saveas=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_SAVE_AS,"SaveAsFile",NULL,NULL,NULL,-1);
    button_undo=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_UNDO,"Undo",NULL,NULL,NULL,-1);
    button_redo=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_REDO,"Redo",NULL,NULL,NULL,-1);
    button_zoomin=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_ZOOM_IN,"Zoom In",NULL,NULL,NULL,-1);
    button_zoomout=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_ZOOM_OUT,"Zoom Out",NULL,NULL,NULL,-1);
    button_fit=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_ZOOM_FIT,"Fit",NULL,NULL,NULL,-1);
    button_rotate=gtk_toolbar_insert_stock(GTK_TOOLBAR(tool_bar),GTK_STOCK_REFRESH,"Rotate",NULL,NULL,NULL,-1);
}


void signals()
{
  /*MenuBarItemsActivateSignals*/
  g_signal_connect(G_OBJECT(menu_item_new),"activate",G_CALLBACK(menu_item_new_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_open),"activate",G_CALLBACK(menu_item_open_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_save),"activate",G_CALLBACK(menu_item_save_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_saveas),"activate",G_CALLBACK(menu_item_saveas_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_quit),"activate",G_CALLBACK(menu_item_quit_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_undo),"activate",G_CALLBACK(menu_item_undo_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_redo),"activate",G_CALLBACK(menu_item_redo_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_zoomin),"activate",G_CALLBACK(menu_item_zoomin_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_zoomout),"activate",G_CALLBACK(menu_item_zoomout_activated),NULL);
  g_signal_connect(G_OBJECT(menu_item_fit),"activate",G_CALLBACK(menu_item_fit_activated),NULL);
  
  /*ToolBarButtonsClickedSignals*/
  g_signal_connect(G_OBJECT(button_new),"clicked",G_CALLBACK(button_new_clicked),NULL);
  g_signal_connect(G_OBJECT(button_open),"clicked",G_CALLBACK(button_open_clicked),NULL);
  g_signal_connect(G_OBJECT(button_save),"clicked",G_CALLBACK(button_save_clicked),NULL);
  g_signal_connect(G_OBJECT(button_saveas),"clicked",G_CALLBACK(button_saveas_clicked),NULL);
  g_signal_connect(G_OBJECT(button_undo),"clicked",G_CALLBACK(button_undo_clicked),NULL);
  g_signal_connect(G_OBJECT(button_redo),"clicked",G_CALLBACK(button_redo_clicked),NULL);
  g_signal_connect(G_OBJECT(button_zoomin),"clicked",G_CALLBACK(button_zoomin_clicked),NULL);
  g_signal_connect(G_OBJECT(button_zoomout),"clicked",G_CALLBACK(button_zoomout_clicked),NULL);
  g_signal_connect(G_OBJECT(button_fit),"clicked",G_CALLBACK(button_fit_clicked),NULL);
  g_signal_connect(G_OBJECT(button_rotate),"clicked",G_CALLBACK(button_rotate_clicked),NULL);
}

int main (int argc, char **argv)
{
	gtk_init (&argc, &argv);
	gtk_gl_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 1100, 700);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	
	/*CreateTheVBox&AttachItToTheMainWindow*/
    vbox=gtk_vbox_new(0,0);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    
    menus_tools();
   	
   	da = gtk_drawing_area_new ();
    gtk_box_pack_start(GTK_BOX(vbox),da,1,1,0);
    
    signals();
    
    
	/* prepare GL */
	glconfig = gdk_gl_config_new_by_mode (
			GDK_GL_MODE_RGB |
			GDK_GL_MODE_DEPTH |
			GDK_GL_MODE_DOUBLE);
			
	gtk_widget_set_events(da, GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK);		

	if (!glconfig)
	{
		g_assert_not_reached ();
	}

	if (!gtk_widget_set_gl_capability (da, glconfig, NULL, 1,
				GDK_GL_RGBA_TYPE))
	{
		g_assert_not_reached ();
	}

	g_signal_connect (da, "configure-event",G_CALLBACK (configure), NULL);
	g_signal_connect (da, "expose-event",G_CALLBACK (expose), NULL);
	g_signal_connect_swapped (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	gtk_signal_connect (GTK_OBJECT (da), "motion_notify_event",(GtkSignalFunc) motion_notify_event, NULL);
	gtk_signal_connect (GTK_OBJECT (da), "button_press_event",(GtkSignalFunc) button_press_event, NULL);
			
    gtk_widget_show (window);
	gtk_widget_show_all (window);
	g_timeout_add (50, rotate, da);
	gtk_main ();
}
