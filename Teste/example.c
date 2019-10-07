#include <cairo.h>
#include <gtk/gtk.h>
#include "Lista.h"
#include "Pontos.h"

static void do_drawing(cairo_t *);


enum {

  LIST_ITEM = 0,
  N_COLUMNS
};

struct {
  int count;
  double coordx[100];
  double coordy[100];
  Lista list;
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{
  do_drawing(cr);

  return FALSE;
}

static void do_drawing(cairo_t *cr)
{
  cairo_set_source_rgb(cr, 255, 0, 0);
  cairo_set_line_width(cr, 0.5);

  int i, j;
    Posic item;
    Ponto ponto;

  for (i = 0; i <= glob.count - 1; i = i+2 ) {
        if(i == 0){
            item = getFirst(glob.list);
        }
        else{
            if(item != NULL)
                item = getNext(glob.list, item);
        }
        if(item != NULL){
            ponto = getItem(glob.list, item);
            cairo_move_to(cr, getPontoX(ponto), getPontoY(ponto));
            item = getNext(glob.list, item);
                    if(item != NULL){
                    ponto = getItem(glob.list, item);
                    cairo_line_to(cr, getPontoX(ponto), getPontoY(ponto));
            }
        }
  }
  cairo_stroke(cr);    
}

static gboolean clicked(GtkWidget *widget, GdkEventButton *event,
    gpointer user_data)
{
    if (event->button == 1) {
        Ponto ponto = createPonto(event->x, event->y);
        ponto = insertLista(glob.list, ponto);
        glob.coordx[glob.count] = event->x;
        glob.coordy[glob.count++] = event->y;
    }

    if (event->button == 1) {
        gtk_widget_queue_draw(widget);
    }

    return TRUE;
}

void quadro(GtkWidget *window){
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  
    GtkWidget *darea;
    glob.list = createLista();

    glob.count = 0;
    
    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
    
    gtk_widget_add_events(window, GDK_BUTTON_PRESS_MASK);

    g_signal_connect(G_OBJECT(darea), "draw", 
        G_CALLBACK(on_draw_event), NULL); 
    g_signal_connect(window, "destroy",
        G_CALLBACK(gtk_main_quit), NULL);  
        
    g_signal_connect(window, "button-press-event", 
        G_CALLBACK(clicked), NULL);

        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
  gtk_window_set_title(GTK_WINDOW(window), "Lines");

  gtk_widget_show_all(window);

  gtk_main();

}

void init_list(GtkWidget *list) {

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("List Items",
          renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), 
      GTK_TREE_MODEL(store));

  g_object_unref(store);
}

void add_to_list(GtkWidget *list, const gchar *str) {
    
  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}

void on_changed(GtkWidget *widget, gpointer label) {
    
  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *value;

  if (gtk_tree_selection_get_selected(
      GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    gtk_label_set_text(GTK_LABEL(label), value);
    g_free(value);
  }
}

void listagem(GtkWidget *window){
     GtkWidget *list;

  GtkWidget *vbox;
  GtkWidget *label;
  GtkTreeSelection *selection; 
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  list = gtk_tree_view_new();

  gtk_window_set_title(GTK_WINDOW(window), "List view");
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);
  gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  vbox = gtk_vbox_new(FALSE, 0);

  gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(window), vbox);

  init_list(list);
  add_to_list(list, "Aliens");
  add_to_list(list, "Leon");
  add_to_list(list, "The Verdict");
  add_to_list(list, "North Face");
  add_to_list(list, "Der Untergang");

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", 
      G_CALLBACK(quadro), G_OBJECT(window));

  g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();
}

void tela_inicial(GtkWidget *window){
    GtkWidget *hbox;
  GtkWidget *vbox;
  GtkWidget *halign;
  GtkWidget *button1;
  GtkWidget *button2;

  vbox = gtk_vbox_new(FALSE, 0);

  hbox = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  halign = gtk_alignment_new(0, 0, 0, 0);
  gtk_container_add(GTK_CONTAINER(halign), hbox);
  gtk_box_pack_start(GTK_BOX(vbox), halign, TRUE, TRUE, 5);

  button1 = gtk_button_new_with_label("Criar Quadro");
  gtk_widget_set_size_request(button1, 200, 300 );
  button2 = gtk_button_new_with_label("Listar Quadros");
  gtk_widget_set_size_request(button2, 200, 300 );

  gtk_box_pack_start(GTK_BOX(hbox), button1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(hbox), button2, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(button1), "clicked", 
           G_CALLBACK(quadro), G_OBJECT(window));

  g_signal_connect(G_OBJECT(button2), "clicked", 
           G_CALLBACK(listagem), G_OBJECT(window));

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); 
  gtk_window_set_title(GTK_WINDOW(window), "Inicial");

  gtk_widget_show_all(window);

  gtk_main();

}


int main(int argc, char *argv[])
{
 GtkWidget *window;

  gtk_init(&argc, &argv);


  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);  
  tela_inicial(window);


  return 0;

  return 0;
  
}