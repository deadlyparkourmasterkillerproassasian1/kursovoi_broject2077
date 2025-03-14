#include "gtk01.h"

static void app_activate (GtkApplication *app, gpointer user_data);

static void open_register_modal_window (GtkWidget *self, gpointer user_data);
static void close_modal_window (GtkWidget *self, gpointer user_data);
static void open_login_modal_window (GtkWidget *self, gpointer user_data);

static void open_profile_modal_window (GtkWidget *self, gpointer user_data);
static void open_settings_modal_window (GtkWidget *self, gpointer user_data);

int main (int argc, char **argv)
{
	GtkApplication *app;
	int             res;

	app = gtk_application_new ("net.MyApp2006", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	res = g_application_run (G_APPLICATION (app), argc, argv);

	g_object_unref (app);
	return res;
}

static void app_activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *window, *grid, *notebook,
		*header_grid, *header_box, *logo_picture, *login_button, *register_button, *profile_button, *settings_button,
		*tab0_label, *tab0_box, *tab0_grid, *tab0_upload_button, *tab0_scrolledwindow, *tab0_listbox, *tab0_download_button, *tab0_outputname_entry, *tab0_outputextension_dropdown, *tab0_rand_button, *tab0_default_button,
		*tab1_label, *tab1_grid, *tab1_info_label, *tab1_flowbox;
	GtkCssProvider *cssprovider;

	cssprovider = gtk_css_provider_new ();
	gtk_css_provider_load_from_path (cssprovider, "style.css");
	gtk_style_context_add_provider_for_display (gdk_display_get_default (), GTK_STYLE_PROVIDER (cssprovider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "MyApp2006");
	gtk_window_set_resizable (GTK_WINDOW (window), 1);
	gtk_window_set_default_size (GTK_WINDOW (window), 960, 540);

	grid = gtk_grid_new ();
	gtk_grid_set_column_spacing (GTK_GRID (grid), 0);
	gtk_grid_set_row_spacing (GTK_GRID (grid), 0);
	gtk_grid_set_column_homogeneous (GTK_GRID (grid), 1);
	gtk_grid_set_row_homogeneous (GTK_GRID (grid), 1);
	
	/*
	 *	HEADER
	*/
	
	header_grid = gtk_grid_new ();
	gtk_grid_set_column_homogeneous (GTK_GRID (header_grid), 1);
	gtk_grid_set_row_homogeneous (GTK_GRID (header_grid), 1);
	gtk_grid_attach (GTK_GRID (grid), header_grid, 0, 0, 1, 1);

	header_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_widget_set_halign (header_box, GTK_ALIGN_END);
	gtk_widget_set_valign (header_box, GTK_ALIGN_END);
	gtk_grid_attach (GTK_GRID (header_grid), header_box, 1, 0, 1, 1);	

	logo_picture = gtk_picture_new_for_filename ("logo.jpg");
	gtk_picture_set_content_fit (GTK_PICTURE (logo_picture), GTK_CONTENT_FIT_FILL);
	gtk_widget_set_halign (logo_picture, GTK_ALIGN_START);
	gtk_widget_set_valign (logo_picture, GTK_ALIGN_FILL);
	gtk_grid_attach (GTK_GRID (header_grid), logo_picture, 0,0, 1, 1);
#if 0	
	login_button = gtk_button_new_with_label ("login");
	gtk_widget_set_halign (login_button, GTK_ALIGN_FILL);
	gtk_widget_set_valign (login_button, GTK_ALIGN_END);
	//gtk_grid_attach (GTK_GRID (header_grid), login_button, 0, 0, 1, 1);
	g_signal_connect (login_button, "clicked", G_CALLBACK (open_login_modal_window), window);
	gtk_box_append (GTK_BOX (header_box), login_button);
	
	register_button = gtk_button_new_with_label ("register");
	gtk_widget_set_halign (register_button, GTK_ALIGN_END);
	gtk_widget_set_valign (register_button, GTK_ALIGN_END);
	g_signal_connect (register_button, "clicked", G_CALLBACK (open_register_modal_window), window);
	//gtk_grid_attach (GTK_GRID (header_grid), register_button, 0, 1, 1, 1);
	gtk_box_append (GTK_BOX (header_box), register_button);
#endif
	profile_button = gtk_button_new_with_label ("profile");
	g_signal_connect (profile_button, "clicked", G_CALLBACK (open_profile_modal_window), window);
	gtk_box_append (GTK_BOX (header_box), profile_button);

	settings_button = gtk_button_new_with_label ("settings");
	g_signal_connect (settings_button, "clicked", G_CALLBACK (open_settings_modal_window), window);
	gtk_box_append (GTK_BOX (header_box), settings_button);

	/*
	 *	TAB_0
	*/
	 
	tab0_label = gtk_label_new ("file");
	
	tab0_grid = gtk_grid_new ();
	gtk_grid_set_column_homogeneous (GTK_GRID (tab0_grid), 1);
	gtk_grid_set_row_homogeneous (GTK_GRID (tab0_grid), 1);
	gtk_widget_set_name (grid, "colored-background");//tab0_grid

	tab0_upload_button = gtk_button_new_with_label ("upload");
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_upload_button, 0, 0, 3, 1);

	tab0_scrolledwindow = gtk_scrolled_window_new ();
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (tab0_scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_scrolled_window_set_overlay_scrolling (GTK_SCROLLED_WINDOW (tab0_scrolledwindow), 0);
	gtk_widget_set_halign (tab0_scrolledwindow, GTK_ALIGN_FILL);
	gtk_widget_set_valign (tab0_scrolledwindow, GTK_ALIGN_FILL);
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_scrolledwindow, 0, 1, 3, 9);

	tab0_listbox = gtk_list_box_new ();
	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (tab0_scrolledwindow), tab0_listbox);

	tab0_download_button = gtk_button_new_with_label ("download");
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_download_button, 3, 0, 3, 1);

	tab0_outputname_entry = gtk_entry_new ();
	gtk_widget_set_halign (tab0_outputname_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (tab0_outputname_entry, GTK_ALIGN_FILL);//START
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_outputname_entry, 3, 1, 2, 1);

	const char *extensions[4] = {"png", "jpeg", "jpg", NULL};
	tab0_outputextension_dropdown = gtk_drop_down_new_from_strings (extensions);
	gtk_widget_set_halign (tab0_outputextension_dropdown, GTK_ALIGN_FILL);//START ?
	gtk_widget_set_valign (tab0_outputextension_dropdown, GTK_ALIGN_FILL);//START
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_outputextension_dropdown, 5, 1, 1, 1);
	
	tab0_rand_button = gtk_button_new_with_label ("random");
	gtk_widget_set_halign (tab0_rand_button, GTK_ALIGN_FILL);
	gtk_widget_set_valign (tab0_rand_button, GTK_ALIGN_START);
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_rand_button, 3, 2, 1, 1);
	
	tab0_default_button = gtk_button_new_with_label ("default");
	gtk_widget_set_halign (tab0_default_button, GTK_ALIGN_FILL);
	gtk_widget_set_valign (tab0_default_button, GTK_ALIGN_START);
	gtk_grid_attach (GTK_GRID (tab0_grid), tab0_default_button, 4, 2, 1, 1);

	/*
	 *	TAB_1
	*/

	tab1_label = gtk_label_new ("preview");
	
	tab1_grid = gtk_grid_new ();
	gtk_grid_set_column_homogeneous (GTK_GRID (tab1_grid), 1);
	gtk_grid_set_row_homogeneous (GTK_GRID (tab1_grid), 1);
	
	tab1_info_label = gtk_label_new ("preview of input files:");
	gtk_widget_set_halign (tab1_info_label, GTK_ALIGN_FILL);
	gtk_widget_set_valign (tab1_info_label, GTK_ALIGN_FILL);
	gtk_label_set_justify (GTK_LABEL (tab1_info_label), GTK_JUSTIFY_LEFT);
	gtk_label_set_xalign (GTK_LABEL (tab1_info_label), 0.025);
	gtk_widget_set_name (tab1_info_label, "colored-background");//__________________________________###
	gtk_grid_attach (GTK_GRID (tab1_grid), tab1_info_label, 0, 0, 1, 1);
	
	tab1_flowbox = gtk_flow_box_new ();
	gtk_widget_set_name (tab1_flowbox, "colored-background");
	gtk_grid_attach (GTK_GRID (tab1_grid), tab1_flowbox, 0, 1, 1, 9);
	
	/*
	 *	NOTEBOOK & WINDOW_STUFF
	*/

	notebook = gtk_notebook_new ();

	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_LEFT);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), tab0_grid, tab0_label);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), tab1_grid, tab1_label);
	gtk_grid_attach (GTK_GRID (grid), notebook, 0, 1, 1, 7);

	gtk_window_set_child (GTK_WINDOW (window), grid);
	gtk_window_present (GTK_WINDOW (window));
}


static void open_register_modal_window (GtkWidget *self, gpointer user_data)
{
	GtkWidget *modalwindow, *box, *login_label, *login_entry, *password_label, *password_entry, *email_label, *email_entry, *register_button;

	/*
	*	WINDOW
	*/
	modalwindow = gtk_window_new ();
	gtk_window_set_modal (GTK_WINDOW (modalwindow), 1);
	gtk_window_set_transient_for (GTK_WINDOW (modalwindow), GTK_WINDOW (user_data));//for linux makes modalwindow always infront
	gtk_window_set_title (GTK_WINDOW (modalwindow), "register_window");
	gtk_window_set_default_size (GTK_WINDOW (modalwindow), 350, 300);
	gtk_window_set_resizable (GTK_WINDOW (modalwindow), 0);

	/*
	 *	WIDGETS
	*/

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_set_homogeneous (GTK_BOX (box), 1);

	login_label = gtk_label_new ("*login:");
	gtk_widget_set_halign (login_label, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (login_label, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), login_label);

	login_entry = gtk_entry_new ();
	gtk_entry_set_placeholder_text (GTK_ENTRY (login_entry), "enter login:");
	gtk_entry_set_max_length (GTK_ENTRY (login_entry), 20);
	gtk_widget_set_halign (login_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (login_entry, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), login_entry);

	password_label = gtk_label_new ("*password:");
	gtk_widget_set_halign (password_label, GTK_ALIGN_FILL);
	gtk_widget_set_valign (password_label, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), password_label);

	password_entry = gtk_entry_new ();
	gtk_entry_set_placeholder_text (GTK_ENTRY (password_entry), "enter password:");
	gtk_entry_set_max_length (GTK_ENTRY (password_entry), 20);
	gtk_widget_set_halign (password_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (password_entry, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), password_entry);

	email_label = gtk_label_new ("email:");
	gtk_widget_set_halign (email_label, GTK_ALIGN_FILL);
	gtk_widget_set_valign (email_label, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), email_label);

	email_entry = gtk_entry_new ();
	gtk_entry_set_placeholder_text (GTK_ENTRY (email_entry), "enter email:");
	gtk_entry_set_max_length (GTK_ENTRY (email_entry), 20);
	gtk_widget_set_halign (email_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (email_entry, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), email_entry);

	register_button = gtk_button_new_with_label ("register");
	gtk_widget_set_halign (register_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (register_button, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), register_button);

	/*
	*	WINDOW_STUFF
	*/
	gtk_window_set_child (GTK_WINDOW (modalwindow), box);

	g_signal_connect (modalwindow, "destroy", G_CALLBACK (close_modal_window), NULL);

	gtk_window_present (GTK_WINDOW (modalwindow));
}

static void close_modal_window (GtkWidget *self, gpointer user_data)
{
	puts ("closed");//no free. it is already freed after closing by gtk or gtk close_functions
}

static void open_login_modal_window (GtkWidget *self, gpointer user_data)
{
	GtkWidget *modalwindow, *box, *login_label, *login_entry, *password_label, *password_entry, *login_button;

	/*
	*	WINDOW
	*/
	modalwindow = gtk_window_new ();
	gtk_window_set_modal (GTK_WINDOW (modalwindow), 1);
	gtk_window_set_transient_for (GTK_WINDOW (modalwindow), GTK_WINDOW (user_data));
	gtk_window_set_title (GTK_WINDOW (modalwindow), "login_window");
	gtk_window_set_default_size (GTK_WINDOW (modalwindow), 350, 300);
	gtk_window_set_resizable (GTK_WINDOW (modalwindow), 0);

	/*
	 *	WIDGETS
	*/

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_set_homogeneous (GTK_BOX (box), 1);

	login_label = gtk_label_new ("*login:");
	gtk_widget_set_halign (login_label, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (login_label, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), login_label);

	login_entry = gtk_entry_new ();
	gtk_entry_set_placeholder_text (GTK_ENTRY (login_entry), "enter login:");
	gtk_entry_set_max_length (GTK_ENTRY (login_entry), 20);
	gtk_widget_set_halign (login_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (login_entry, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), login_entry);

	password_label = gtk_label_new ("*password:");
	gtk_widget_set_halign (password_label, GTK_ALIGN_FILL);
	gtk_widget_set_valign (password_label, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), password_label);

	password_entry = gtk_entry_new ();
	gtk_entry_set_placeholder_text (GTK_ENTRY (password_entry), "enter password:");
	gtk_entry_set_max_length (GTK_ENTRY (password_entry), 20);
	gtk_widget_set_halign (password_entry, GTK_ALIGN_FILL);
	gtk_widget_set_valign (password_entry, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), password_entry);

	login_button = gtk_button_new_with_label ("login");
	gtk_widget_set_halign (login_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (login_button, GTK_ALIGN_CENTER);
	gtk_box_append (GTK_BOX (box), login_button);

	/*
	*	WINDOW_STUFF
	*/
	gtk_window_set_child (GTK_WINDOW (modalwindow), box);

	g_signal_connect (modalwindow, "destroy", G_CALLBACK (close_modal_window), NULL);

	gtk_window_present (GTK_WINDOW (modalwindow));
}

static void open_profile_modal_window (GtkWidget *self, gpointer user_data)
{
	GtkWidget *modalwindow, *grid, *info_box, *profile_picture, *login_label, *email_label, *logout_button;

	/*
	*	WINDOW
	*/
	modalwindow = gtk_window_new ();
	gtk_window_set_modal (GTK_WINDOW (modalwindow), 1);
	gtk_window_set_transient_for (GTK_WINDOW (modalwindow), GTK_WINDOW (user_data));
	gtk_window_set_title (GTK_WINDOW (modalwindow), "profile_window");
	gtk_window_set_resizable (GTK_WINDOW (modalwindow), 0);
	gtk_window_set_default_size (GTK_WINDOW (modalwindow), 350, 350);

	/*
	*	WIDGETS
	*/

	//box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	//gtk_box_set_homogeneous (GTK_BOX (box), 1);
	grid = gtk_grid_new ();
	gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (grid, GTK_ALIGN_FILL);

	profile_picture = gtk_picture_new_for_filename ("profile.png");
	gtk_picture_set_content_fit (GTK_PICTURE (profile_picture), GTK_CONTENT_FIT_CONTAIN);
	//gtk_box_append (GTK_BOX (box), profile_picture);
	gtk_grid_attach (GTK_GRID (grid), profile_picture, 0, 0, 1, 1);

	info_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_widget_set_halign (info_box, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (info_box, GTK_ALIGN_FILL);
	gtk_grid_attach (GTK_GRID (grid), info_box, 0, 1, 1, 1);
	//gtk_widget_set_name (info_box, "colored-background");

	login_label = gtk_label_new ("login:\n*********");
	gtk_widget_set_halign (login_label, GTK_ALIGN_START);
	gtk_widget_set_valign (login_label, GTK_ALIGN_FILL);
	gtk_box_append (GTK_BOX (info_box), login_label);
	//gtk_grid_attach (GTK_GRID (grid), login_label, 0, 1, 1, 1);

	email_label = gtk_label_new ("email:\n**************");
	gtk_widget_set_halign (email_label, GTK_ALIGN_START);
	gtk_widget_set_valign (email_label, GTK_ALIGN_FILL);
	gtk_box_append (GTK_BOX (info_box), email_label);
	//gtk_grid_attach (GTK_GRID (grid), email_label, 0, 2, 1, 1);

	logout_button = gtk_button_new_with_label ("logout");
	gtk_widget_set_halign (logout_button, GTK_ALIGN_CENTER);
	gtk_widget_set_valign (logout_button, GTK_ALIGN_END);
	//gtk_box_append (GTK_BOX (box), logout_button);
	gtk_grid_attach (GTK_GRID (grid), logout_button, 0, 3, 1, 1);

	/*
	*	WINDOW_STUFF
	*/

	g_signal_connect (modalwindow, "destroy", G_CALLBACK (close_modal_window), NULL);
	gtk_window_set_child (GTK_WINDOW (modalwindow), grid);

	gtk_window_present (GTK_WINDOW (modalwindow));
}

static void open_settings_modal_window (GtkWidget *self, gpointer user_data)
{//notebook tab0 - language, tab1 - notifications a lot 1,2,3...
	GtkWidget *modalwindow, *grid, *notebook, 
		*tab0_label, *tab0_box, *tab0_info_label, *tab0_languages_dropdown,
		*tab1_label, *tab1_grid, //.....
		*buttons_box, *save_button, *default_button, *cancel_button;
	const char *languages[4];
	/*
	*	WINDOW
	*/
	modalwindow = gtk_window_new ();
	gtk_window_set_modal (GTK_WINDOW (modalwindow), 1);
	gtk_window_set_transient_for (GTK_WINDOW (modalwindow), GTK_WINDOW (user_data));
	gtk_window_set_title (GTK_WINDOW (modalwindow), "settings_window");
	gtk_window_set_resizable (GTK_WINDOW (modalwindow), 0);
	gtk_window_set_default_size (GTK_WINDOW (modalwindow), 400, 300);
	
	/*
	*	WIDGETS
	*/
	
	grid = gtk_grid_new ();
	gtk_widget_set_halign (grid, GTK_ALIGN_FILL);
	gtk_widget_set_valign (grid, GTK_ALIGN_FILL);
	gtk_grid_set_column_homogeneous (GTK_GRID (grid), 1);
	gtk_grid_set_row_homogeneous (GTK_GRID (grid), 1);

	notebook = gtk_notebook_new ();
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_LEFT);
	gtk_widget_set_halign (notebook, GTK_ALIGN_FILL);
	gtk_widget_set_valign (notebook, GTK_ALIGN_FILL);
	gtk_grid_attach (GTK_GRID (grid), notebook, 0, 0, 1, 8);
	
	/*
	*	TAB0
	*/
	
	tab0_label = gtk_label_new ("language");
	tab0_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	
	tab0_info_label = gtk_label_new ("selected language:");
	gtk_box_append (GTK_BOX (tab0_box), tab0_info_label);
	
	languages[0] = "Russian";
	languages[1] = "English";
	languages[2] =  "aoifjgoi!";
	languages[3] = NULL;
	tab0_languages_dropdown = gtk_drop_down_new_from_strings (languages);
	gtk_box_append (GTK_BOX (tab0_box), tab0_languages_dropdown);
	
	/*
	*	TAB1
	*/
	
	tab1_label = gtk_label_new ("notifications");
	tab1_grid = gtk_grid_new ();	
	
	/*
	*	BUTTONS
	*/
	buttons_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_set_homogeneous (GTK_BOX (buttons_box), 1);
	gtk_widget_set_halign (buttons_box, GTK_ALIGN_FILL);
	gtk_widget_set_valign (buttons_box, GTK_ALIGN_FILL);
	gtk_grid_attach (GTK_GRID (grid), buttons_box, 0, 8, 1, 1);
	gtk_widget_set_name (buttons_box, "colored-background");
	
	save_button = gtk_button_new_with_label ("save");
	//gtk_widget_set_halign (save_button, GTK_ALIGN_FILL);
	//gtk_widget_set_valign (save_button, GTK_ALIGN_FILL);
	gtk_box_append (GTK_BOX (buttons_box), save_button);
	
	default_button = gtk_button_new_with_label ("default");
	//gtk_widget_set_halign (default_button, GTK_ALIGN_FILL);
	//gtk_widget_set_valign (default_button, GTK_ALIGN_FILL);
	gtk_box_append (GTK_BOX (buttons_box), default_button);
	
	cancel_button = gtk_button_new_with_label ("cancel");
	//gtk_widget_set_halign (cancel_button, GTK_ALIGN_FILL);
	//gtk_widget_set_valign (cancel_button, GTK_ALIGN_FILL);
	gtk_box_append (GTK_BOX (buttons_box), cancel_button);puts ("lol");
	
	/*
	*	NOTEBOOK & WINDOW_STUFF
	*/
	
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), tab0_box, tab0_label);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), tab1_grid, tab1_label);
	
	g_signal_connect (modalwindow, "destroy", G_CALLBACK (close_modal_window), NULL);
	gtk_window_set_child (GTK_WINDOW (modalwindow), grid);

	gtk_window_present (GTK_WINDOW (modalwindow));
}

/*
	open_login_modal_window & open_register_modal_window создать одну функцию, которая возвращает окно с логином, паролем и вызывать эту функицю в этих 2х функциях ???? - Не очень, нехочу.


*/
