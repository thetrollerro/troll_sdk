#include "menu.hpp"
#include "imgui/imgui_internal.h"


#define MainMenuColor ImVec4( 1.f, 0.f, 0.f, 1.f )

std::string to_lower( std::string str ) {
	std::transform( str.begin( ), str.end( ), str.begin( ), ( int( * )( int ) )std::tolower );
	return str;
}

#pragma region custom_imgui

namespace ImGui {

	bool ColorPicker( const char* label, float* color, bool alpha = true, bool sameline = true ) {
		if ( sameline ) {
			SameLine( );
		}

		const ImVec4 col_v4( color[ 0 ], color[ 1 ], color[ 2 ], alpha ? color[ 3 ] : 1.0f );

		std::string id_colorbutton_new = label;
		id_colorbutton_new += "##color_button";

		std::string id_new = label;
		id_new += "##picker";

		bool open_popup = ColorButton( id_colorbutton_new.c_str( ), col_v4,
			ImGuiColorEditFlags_NoSidePreview |
			ImGuiColorEditFlags_NoSmallPreview |
			ImGuiColorEditFlags_AlphaPreview |
			ImGuiColorEditFlags_NoTooltip, ImVec2( 20, 0 ) );

		if ( open_popup )
		{
			OpenPopup( id_new.c_str( ) );
		}

		if ( BeginPopup( id_new.c_str( ) ) )
		{
			ColorPicker4( id_new.c_str( ), color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_PickerHueBar | ( alpha ? ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_AlphaBar : 0 ) );
			EndPopup( );
		}

		return true;
	}

	template<size_t N>
	bool ButtonTab( const char* ( &names )[ N ], int& active_tab, int height = 20, bool no_spacing = true, bool inv_background = false, bool sameline = true ) {
		bool _ret;
		for ( auto i = 0; i < N; ++i ) {

			/* push style vars */
			if ( no_spacing ) {
				PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );
			}

			/* push style colors */
			if ( inv_background ) {
				PushStyleColor( ImGuiCol_Button, ( active_tab == i ) ? ImVec4( 0.04f, 0.04f, 0.04f, 0.f ) : ImVec4( 0.06f, 0.06f, 0.06f, 1.f ) );
				PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.06f, 0.06f, 0.06f, ( active_tab == i ) ? 0.2f : 0.3f ) );
				PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.04f, 0.04f, 0.04f, ( active_tab == i ) ? 0.2f : 0.3f ) );
			}
			else {
				PushStyleColor( ImGuiCol_Text, ( active_tab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
				PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 1.00f ) );
				PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 1.00f ) );
			}

			/* button */
			_ret = Button( names[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( names ), height ) );
			if ( _ret ) active_tab = i;

			/* do sameline */
			if ( sameline ) {
				SameLine( );
			}

			/* pop style vars */
			if ( no_spacing ) {
				PopStyleVar( );
			}

			/* pop style colors */
			PopStyleColor( 3 );

		}
		return _ret;
	}
}

#pragma endregion


void menu::init( ) {
	/* start imgui */
	ImGui_ImplDX9_NewFrame( );

	/* draw the menu */
	menu::render( );

	/* end imgui */
	ImGui::Render( );
}

void menu::render( ) {
	/* draw menu only when opened */
	if ( !menu::opened ) return;

	/* get tabs */
	const char* tabs[ ] = { "Rage", "Antiaim", "Legit", "Visuals", "Misc" };
	enum tab_select : int {
		rage, antiaim, legit, visuals, misc
	};

	/* vars */
	static int current_tab = visuals;
	ImGui::SetNextWindowSize( ImVec2( 800, 440 ), ImGuiCond_Always );
	ImGui::Begin( "TrollerWare.xyz", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );
	{

		/* draw tabs on top */ {
			ImGui::BeginGroup( ); {
				ImGui::ButtonTab( tabs, current_tab );
			}
			ImGui::EndGroup( );
		}

		/* begin childs */ {
			ImGui::BeginChild( "##main_child", ImVec2( -1, -1 ), true ); {

				/* push colors for new childs */
				ImGui::PushStyleColor( ImGuiCol_ChildWindowBg, ImVec4( 0.04f, 0.04f, 0.04f, 1.f ) );
				ImGui::PushStyleColor( ImGuiCol_Border, ImVec4( 0.01f, 0.01f, 0.01f, 0.6f ) );

				/* draw tabs */
				switch ( current_tab ) {
				case rage:
					rage_tab( );
					break;
				case antiaim:
					antiaim_tab( );
					break;
				case legit:
					legit_tab( );
					break;
				case visuals:
					esp_tab( );
					break;
				case misc:
					misc_tab( );
					break;
				};

				/* pop colors */
				ImGui::PopStyleColor( 2 );
			}
			ImGui::EndChild( );
		}

	}
	ImGui::End( );
}

void menu::style( IDirect3DDevice9* dev ) {
	ImGui_ImplDX9_Init( hooks::csgo_window, dev );

	/* add font */
	ImGuiIO& io = ImGui::GetIO( );
	io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\Impact.ttf", 13.f, NULL, io.Fonts->GetGlyphRangesDefault( ) );


	ImGuiStyle& style = ImGui::GetStyle( );
	style.Alpha = 1.f;
	style.WindowTitleAlign = ImVec2( 0.5f, 0.5f );
	style.ItemSpacing = ImVec2( 6.f, 3.f );
	style.ItemInnerSpacing = ImVec2( 6.f, 4.f );
	style.FrameRounding = 0.f;
	style.ColumnsMinSpacing = 0.f;
	style.GrabRounding = 6.f;
	style.AntiAliasedLines = true;
	style.WindowRounding = 0.f;
	style.FramePadding = ImVec2( 2.f, 2.f );
	style.ScrollbarSize = 6.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 6.f;


	style.Colors[ ImGuiCol_Text ] = ImVec4( 0.90f, 0.90f, 0.90f, 1.00f );
	style.Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
	style.Colors[ ImGuiCol_WindowBg ] = ImColor( 12, 12, 12, 255 ); // ImVec4( 0.04f, 0.04f, 0.04f /*12*/, 0.9f /*230*/ );
	style.Colors[ ImGuiCol_ChildWindowBg ] = ImColor( 15, 15, 15, 255 ); // ImVec4( 0.06f, 0.06f, 0.06f, 1.f );
	style.Colors[ ImGuiCol_PopupBg ] = ImVec4( 0.08f, 0.08f, 0.08f, 0.94f );
	style.Colors[ ImGuiCol_Border ] = ImVec4( 0.06f, 0.06f, 0.06f, 0.2f );//MainMenuColor;
	style.Colors[ ImGuiCol_BorderShadow ] = ImVec4( 0.04f, 0.04f, 0.04f, 0.5f );//ImVec4( 0.06f, 0.06f, 0.06f, 0.01f );
	style.Colors[ ImGuiCol_FrameBg ] = ImVec4( 0.10f, 0.10f, 0.10f, 0.71f );
	style.Colors[ ImGuiCol_FrameBgHovered ] = MainMenuColor;
	style.Colors[ ImGuiCol_FrameBgActive ] = MainMenuColor;
	style.Colors[ ImGuiCol_TitleBg ] = ImVec4( 0.07f, 0.07f, 0.07f, 0.48f );
	style.Colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.07f, 0.07f, 0.07f, 0.48f );
	style.Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.07f, 0.07f, 0.07f, 0.48f );
	style.Colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.10f, 0.10f, 0.10f, 0.66f );
	style.Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.00f );
	style.Colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.31f, 0.31f, 0.31f, 1.00f );
	style.Colors[ ImGuiCol_ScrollbarGrabHovered ] = MainMenuColor;
	style.Colors[ ImGuiCol_ScrollbarGrabActive ] = MainMenuColor;
	style.Colors[ ImGuiCol_CheckMark ] = MainMenuColor;
	style.Colors[ ImGuiCol_SliderGrab ] = ImVec4( 0.29f, 0.29f, 0.29f, 1.00f );
	style.Colors[ ImGuiCol_SliderGrabActive ] = MainMenuColor;
	style.Colors[ ImGuiCol_Button ] = ImVec4( 0.01f, 0.01f, 0.01f, 1.00f );
	style.Colors[ ImGuiCol_ButtonHovered ] = MainMenuColor;
	style.Colors[ ImGuiCol_ButtonActive ] = MainMenuColor;

	style.Colors[ ImGuiCol_Header ] = MainMenuColor;
	style.Colors[ ImGuiCol_HeaderHovered ] = MainMenuColor;
	style.Colors[ ImGuiCol_HeaderActive ] = MainMenuColor;
	style.Colors[ ImGuiCol_ResizeGrip ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.25f );
	style.Colors[ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.67f );
	style.Colors[ ImGuiCol_ResizeGripActive ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.95f );
	style.Colors[ ImGuiCol_PlotLines ] = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	style.Colors[ ImGuiCol_PlotLinesHovered ] = ImVec4( 1.00f, 1.00f, 1.00f, 1.00f );
	style.Colors[ ImGuiCol_PlotHistogram ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	style.Colors[ ImGuiCol_PlotHistogramHovered ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	style.Colors[ ImGuiCol_TextSelectedBg ] = MainMenuColor;
	style.Colors[ ImGuiCol_ModalWindowDarkening ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
}

void menu::rage_tab( ) {
	/* get sub_tabs etc. */
	const char* sub_tabs[ ] = { "Auto", "Scout", "AWP", "Heavy Pistol", "Other" };
	enum sub_tab : int {
		auto_,
		scout,
		awp,
		heavy_pistol,
		other,
		ignore_lasttab
	};
	static int m_subtab = auto_;

	/* set columns number */
	ImGui::Columns( 2, NULL, false );

	/* set columns offset */
	ImGui::SetColumnOffset( 1, 310 );

	/* begin the child for general_subtab */ {
		ImGui::BeginChild( "##general_subtab", ImVec2( 300, -1 ), true ); {
			
		}
		ImGui::EndChild( );
	}

	/* go to next column */
	ImGui::NextColumn( );

	/* begin the child for select_subtab */ {
		ImGui::BeginChild( ( "##select_subtab" ), ImVec2( -1, 36 ), true ); {
			for ( auto i = 0; i < ignore_lasttab; ++i ) {

				/* push style vars */
				ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );

				/* push style colors */
				ImGui::PushStyleColor( ImGuiCol_Text, ( m_subtab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
				ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );

				if ( ImGui::Button( sub_tabs[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( sub_tabs ), 20.f ) ) ) {
					m_subtab = i;
				}

				ImGui::SameLine( );

				/* pop style vars */
				ImGui::PopStyleVar( 1 );

				/* pop style colors */
				ImGui::PopStyleColor( 4 );

			}
		}
		ImGui::EndChild( );
	}

	/* begin the child for the current subtab */ {
		ImGui::BeginChild( "##weapon_subtab", ImVec2( -1, -1 ), true ); {
			switch ( m_subtab ) {

			case auto_: break;
			case scout: break;
			case awp: break;
			case heavy_pistol: break;
			case other: break;

			};
		}ImGui::EndChild( );
	}

	/* reset columns */
	ImGui::Columns( 1, NULL, false );
}

void menu::antiaim_tab( ) {
	/* get vars */
	const char* pitch[ ] = { "Off", "Down", "Up", "Dynamic" };
	const char* yaw[ ] = { "Off", "Backwards", "Manual" };
	const char* desync[ ] = { "Off", "Static", "Double Static", "Tension" };

	/* change columns nr */
	ImGui::Columns( 2, NULL, false );

	/* set columns offset */
	ImGui::SetColumnOffset( 1, 310 );

	ImGui::BeginChild( "##mainaa_subtab", ImVec2( 300, -1 ), true ); {
		
	}ImGui::EndChild( );

	/* go to next column */
	ImGui::NextColumn( );

	ImGui::BeginChild( "##otheraa_subtab", ImVec2( -1, -1 ), true ); {
		
	}ImGui::EndChild( );

	/* reset columns nr */
	ImGui::Columns( 1, NULL, false );
}

void menu::legit_tab( ) {
	/* get sub_tabs etc. */
	const char* sub_tabs[ ] = { "Pistols", "Others", "Snipers" };
	enum sub_tab : int {
		pistols,
		others,
		snipers,
		ignore_lasttab
	};
	static int m_subtab = pistols;

	/* set columns number */
	ImGui::Columns( 2, NULL, false );

	/* set columns offset */
	ImGui::SetColumnOffset( 1, 310 );

	/* begin the child for select_subtab */ {
		ImGui::BeginChild( "##select_subtab", ImVec2( 300, 36 ), true ); {
			for ( auto i = 0; i < ignore_lasttab; ++i ) {

				/* push style vars */
				ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );

				/* push style colors */
				ImGui::PushStyleColor( ImGuiCol_Text, ( m_subtab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
				ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );

				if ( ImGui::Button( sub_tabs[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( sub_tabs ), 20.f ) ) ) {
					m_subtab = i;
				}

				ImGui::SameLine( );

				/* pop style vars */
				ImGui::PopStyleVar( 1 );

				/* pop style colors */
				ImGui::PopStyleColor( 4 );

			}
		}
		ImGui::EndChild( );
	}

	/* begin the child for general_subtab */ {
		const char* legitbot_type[ ] = { "On Shoot", "On Key" };
		const char* legitaa_type[ ] = { "Normal", "Double" };
		ImGui::BeginChild( "##general_subtab", ImVec2( 300, -1 ), true ); {
			
		}
		ImGui::EndChild( );
	}

	/* go to next column */
	ImGui::NextColumn( );

	/* begin the child for the current subtab */ {
		const char* aim_type[ ] = { "Solid", "Sleek", "Reserved" };
		const char* hitboxes[ ] = { "Head", "Neck" , "Chest", "Nearest" };
		ImGui::BeginChild( "##aimbot_subtab", ImVec2( -1, -1 ), true ); {
			switch ( m_subtab ) {

			case pistols:  break;

			case others:  break;

			case snipers: break;

			};
		}ImGui::EndChild( );
	}

	/* reset columns */
	ImGui::Columns( 1, NULL, false );
}

void menu::esp_tab( ) {
	/* get sub_tabs etc. */
	const char* sub_tabs[ ] = { "Players", "Chams", "Glow", "World" };
	enum sub_tab : int {
		players,
		chams,
		glow,
		world,
		ignore_lasttab
	};
	static int m_subtab = players;

	/* set columns number */
	ImGui::Columns( 2, NULL, false );

	/* set columns offset */
	ImGui::SetColumnOffset( 1, 310 );

	/* begin the child for select_subtab */ {
		ImGui::BeginChild( "##select_subtab", ImVec2( 300, 36 ), true ); {
			for ( auto i = 0; i < ignore_lasttab; ++i ) {

				/* push style vars */
				ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );

				/* push style colors */
				ImGui::PushStyleColor( ImGuiCol_Text, ( m_subtab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
				ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );

				if ( ImGui::Button( sub_tabs[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( sub_tabs ), 20.f ) ) ) {
					m_subtab = i;
				}

				ImGui::SameLine( );

				/* pop style vars */
				ImGui::PopStyleVar( 1 );

				/* pop style colors */
				ImGui::PopStyleColor( 4 );

			}
		}
		ImGui::EndChild( );
	}

	/* begin the child for other_subtab */ {
		const char* tp_ang[ ] = { "Real Angle", "Fake Angle" };
		ImGui::BeginChild( "##other_subtab", ImVec2( 300, -1 ), true ); {
		}
		ImGui::EndChild( );
	}

	/* go to next column */
	ImGui::NextColumn( );

	/* begin the child for the current subtab */ {
		const char* esp_type[ ] = { "Static", "Dynamic" };
		switch ( m_subtab ) {

		case players: {
			ImGui::BeginChild( "##player_subtab", ImVec2( -1, -1 ), true ); {
				
			}
			ImGui::EndChild( );
		} break;

		case chams: {

			/* get sub_tabs etc. */
			const char* chams_subtabs[ ] = { "Enemies", "Local", "Desync" , "Hand" , "Weapon" };
			enum chams_subtab : int {
				enemies,
				local,
				desync,
				hand,
				weapon,
				ignore_lastsubtab_chams
			};
			static int m_chams_subtab;

			/* begin child for select_chams_subtab */ {
				ImGui::BeginChild( "##select_chams_subtab", ImVec2( -1, 36 ), true ); {
					for ( auto i = 0; i < ignore_lastsubtab_chams; ++i ) {

						/* push style vars */
						ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );

						/* push style colors */
						ImGui::PushStyleColor( ImGuiCol_Text, ( m_chams_subtab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
						ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
						ImGui::PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
						ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );

						if ( ImGui::Button( chams_subtabs[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( chams_subtabs ), 20.f ) ) ) {
							m_chams_subtab = i;
						}

						ImGui::SameLine( );

						/* pop style vars */
						ImGui::PopStyleVar( 1 );

						/* pop style colors */
						ImGui::PopStyleColor( 4 );

					}
				}
				ImGui::EndChild( );
			}

			/* begin child for chams_subtab */ {
				const char* material_types[ ] = { "Flat", "Textured", "Metallic", "Pulsing" };
				const char* overlay_types[ ] = { "Glow", "Glow Outline", "Wireframe" };
				ImGui::BeginChild( "##chams_subtab", ImVec2( -1, -1 ), true ); {
					switch ( m_chams_subtab ) {

					case enemies:  break;

					case local:  break;

					case desync:  break;

					case hand:  break;

					case weapon:  break;

					};
				}
				ImGui::EndChild( );
			}

		} break;

		case glow: {

		}break;

		case world: {
			ImGui::BeginChild( "##world_subtab", ImVec2( -1, -1 ), true ); {
				
			}ImGui::EndChild( );
		}break;
		};
	}

	/* reset columns */
	ImGui::Columns( 1, NULL, false );
}

void menu::misc_tab( ) {
	/* get sub_tabs etc. */
	const char* sub_tabs[ ] = { "Fakelag", "Buybot", "Config", "Skins" };
	enum sub_tab : int {
		fakelag,
		buybot,
		config,
		skins,
		ignore_lasttab
	};
	static int m_subtab = fakelag;

	/* set columns number */
	ImGui::Columns( 2, NULL, false );

	/* set columns offset */
	ImGui::SetColumnOffset( 1, 310 );

	/* begin the child for select_subtab */ {
		ImGui::BeginChild( "##select_subtab", ImVec2( 300, 36 ), true ); {
			for ( auto i = 0; i < ignore_lasttab; ++i ) {

				/* push style vars */
				ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );

				/* push style colors */
				ImGui::PushStyleColor( ImGuiCol_Text, ( m_subtab == i ) ? MainMenuColor : ImVec4( 0.90f, 0.90f, 0.90f, 1.f ) );
				ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonActive, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );
				ImGui::PushStyleColor( ImGuiCol_ButtonHovered, ImVec4( 0.01f, 0.01f, 0.01f, 0.f ) );

				if ( ImGui::Button( sub_tabs[ i ], ImVec2( ( ImGui::GetWindowSize( ).x - ImGui::GetStyle( ).WindowPadding.x * 2 ) / _countof( sub_tabs ), 20.f ) ) ) {
					m_subtab = i;
				}

				ImGui::SameLine( );

				/* pop style vars */
				ImGui::PopStyleVar( 1 );

				/* pop style colors */
				ImGui::PopStyleColor( 4 );

			}
		}
		ImGui::EndChild( );
	}

	/* begin the child for general_subtab */ {
		ImGui::BeginChild( "##general_subtab", ImVec2( 300, -1 ), true ); {

			if ( m_subtab != skins ) {
				
			}
			else {
				
			}
		}
		ImGui::EndChild( );
	}

	/* go to next column */
	ImGui::NextColumn( );

	/* begin the child for the current subtab */ {
		ImGui::BeginChild( "##misc_subtab", ImVec2( -1, -1 ), true ); {
			switch ( m_subtab ) {

			case fakelag: {
			
			} break;

			case buybot: {

			} break;

			case config: {
				get_config( );
				ImGui::Spacing( );
				if ( ImGui::Combo( "cfg", &selectedcfg, [ ] ( void* data, int idx, const char** out_text )
				{
					*out_text = configs[ idx ].c_str( );
					return true;
				}, nullptr, configs.size( ), 10 ) )
				{
					cfgname = configs[ selectedcfg ];
					cfgname.erase( cfgname.length( ) - 4, 4 );
					strcpy( g_vars.misc.config_name, cfgname.c_str( ) );
				}

				ImGui::Spacing( );

				static bool create;
				if ( ImGui::Button( "Save" ) )
				{
					g_vars.save_config( );
				}
				ImGui::SameLine( );
				if ( ImGui::Button( "Load" ) )
				{
					g_vars.load_config( );
				}

				ImGui::Spacing( );

				if ( ImGui::Button( "New config", ImVec2( -1, 15 ) ) ) create = !create;
				if ( ImGui::Button( "reset settings", ImVec2( -1, 15 ) ) ) g_vars.setup_config( );

				if ( create )
				{
					ImGui::SetNextWindowSize( ImVec2( 260, 160 ), ImGuiCond_Always );
					ImGui::Begin( "##createconfig", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar );
					{
						ImGui::Text( "Config name:" );
						ImGui::InputText( "Name", g_vars.misc.config_name, 52 );
						if ( ImGui::Button( "Create & Save", ImVec2( -1, 15 ) ) )
						{
							g_vars.save_config( );
							create = !create;
						}
						if ( ImGui::Button( "Cancel", ImVec2( -1, 15 ) ) )
							create = !create;
						ImGui::End( );
					}
				}
			}break;

			case skins: {

			}break;
			};
		}ImGui::EndChild( );
	}

	/* reset columns */
	ImGui::Columns( 1, NULL, false );
}
