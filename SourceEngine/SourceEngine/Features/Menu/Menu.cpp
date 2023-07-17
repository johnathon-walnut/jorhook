#include "Menu.h"
#include "Input/Input.h"

#include "../Vars.h"

//TODO: stop using me
namespace InputHelper
{
	enum State_t
	{
		NONE,
		PRESSED,
		HELD
	};

	State_t keys[256] = { NONE };
	std::chrono::time_point<std::chrono::steady_clock> start[256] = { std::chrono::steady_clock::now() };

	void Update()
	{
		for (int n = 0; n < 256; n++)
		{
			if (GetKeyState(n) & 0x8000)
			{
				if (keys[n] == PRESSED)
				{
					keys[n] = HELD;
				}
				else if (keys[n] != HELD)
				{
					keys[n] = PRESSED;
				}
			}
			else
			{
				keys[n] = NONE;
			}
		}
	}

	bool IsPressed(int16_t key)
	{
		return (keys[key] == PRESSED);
	}

	bool IsHeld(int16_t key)
	{
		return (keys[key] == HELD);
	}

	bool IsPressedAndHeld(int16_t key)
	{
		State_t key_state = keys[key];

		if (key_state == PRESSED)
		{
			start[key] = std::chrono::steady_clock::now();
			return true;
		}

		if (key_state == HELD && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start[key]).count() > 400)
		{
			return true;
		}

		return false;
	}
}

#define COLOR_OPTION(name, var) new CItemClrGroup { name, { new CItemClr("Red", &var, EClrType::r), new CItemClr("Green", &var, EClrType::g), new CItemClr("Blue", &var, EClrType::b), new CItemClr("Alpha", &var, EClrType::a) }, false, EItemType::COLOR, &var}

void CMenu::CreateLists()
{
	static bool bDone = false;

	if (!bDone)
	{
		m_ItemLists =
		{
			new CItemList
			{
				"Main",
				{
					new CItemGroup
					{
						"Aimbot",
						{
							new CItemBool("Enabled", &V::Aimbot_Enabled),
							new CItemKey("Aim key", &V::Aimbot_AimKey),
							new CItemInt("Hitbox", &V::Aimbot_Hitbox, { {0, "Auto"}, {1, "Head"}, {2, "Body"}}, 0, 2),
							new CItemInt("FoV max", &V::Aimbot_FoV,{}, 0, 180),

						}
					},
					new CItemGroup
					{
						"Movement",
						{
							new CItemBool("Bunnyhop", &V::Movement_Bunnyhop),
							new CItemBool("No push", &V::Movement_NoPush),
						}
					},
					new CItemGroup
					{
						"Exploits",
						{
							new CItemKey("Sequence freezing", &V::Exploits_SequenceFreezing_Key),
							new CItemInt("Sequence freeze value", &V::Exploits_SequenceFreezing_Value),
							new CItemKey("Airstuck key", &V::Exploits_Airstuck_Key),
						}
					},
					new CItemGroup
					{
						"Config",
						{
							new CItemButton("Save", []() { CFG::Save("jorhook"); }),
							new CItemButton("Load", []() { CFG::Load("jorhook"); }),
						}
					}
				}
			},

			new CItemList
			{
				"Visuals",
				{
					new CItemGroup
					{
						"Player ESP",
						{
							new CItemBool("Enabled", &V::ESP_Enabled),
							new CItemBool("Outlined", &V::ESP_Outline),
							new CItemBool("Enemy only", &V::ESP_EnemyOnly),
							new CItemBool("Show local", &V::ESP_ShowLocal),
							new CItemBool("Name", &V::ESP_Name),
							new CItemBool("Box", &V::ESP_Box),
							new CItemBool("Health", &V::ESP_Health),
							new CItemBool("Armour", &V::ESP_Armour),
							new CItemBool("Distance", &V::ESP_Distance),
						}
					},
					new CItemGroup
					{
						"Player chams",
						{
							new CItemBool("Enabled", &V::Chams_Enabled),						//, true);
							new CItemBool("Enemy only", &V::Chams_EnemyOnly),
							new CItemBool("Show local", &V::Chams_ShowLocal),
							new CItemInt("Invisible material", &V::Chams_OccludedMaterial, {{0, "None"}, {1, "Shaded"}, {2, "Flat"}}, 0, 2),						//, 1); // None, Shaded, Flat, Shiny
							new CItemInt("Visible material", &V::Chams_UnoccludedMaterial, {{0, "None"}, {1, "Shaded"}, {2, "Flat"}}, 0, 2),						//, 0); // None, Shaded, Flat, Shiny
							new CItemBool("Invis use color", &V::Chams_OccludedUseCustomColor),						//, false);
							new CItemBool("Vis use color", &V::Chams_UnoccludedUseCustomColor),						//, false);
						}
					},
					new CItemGroup
					{
					"Player glow",
						{
							new CItemBool("Enabled", &V::Glow_Enabled),
							new CItemBool("Enemy only", &V::Glow_EnemyOnly),
							new CItemBool("Show local", &V::Glow_ShowLocal),
						}
					},
					new CItemGroup
					{
						"Visuals",
						{
							new CItemInt("FoV override", &V::Misc_FoV,{},70, 150),
							new CItemBool("Show aimbot FoV", &V::Misc_Show_Aimbot_FoV),
							new CItemBool("Remove view punch", &V::Misc_Remove_Visual_Punch),
						}
					},
					new CItemGroup
					{
						"Menu",
						{
							new CItemInt("List Width", &V::Menu_ListWidth),
							new CItemInt("List bar height", &V::Menu_ListBarH),
							new CItemInt("Group height", &V::Menu_GroupH),
						}
					},
				}
			},

			new CItemList
			{
				"Colours",
				{
					COLOR_OPTION("Outline", V::Colors_OutlineColor),
					COLOR_OPTION("Condition", V::Colors_CondColor),
					COLOR_OPTION("Target", V::Colors_TargetColor),
					COLOR_OPTION("Invulnerable", V::Colors_InvulnColor),
					COLOR_OPTION("Cloaked", V::Colors_CloakColor),
					COLOR_OPTION("Friend", V::Colors_FriendColor),
					COLOR_OPTION("Overheal", V::Colors_OverhealColor),
					COLOR_OPTION("Enemy", V::Colors_EnemyColor),
					COLOR_OPTION("Team", V::Colors_TeamColor),
					COLOR_OPTION("Health low", V::ESP_HealthLow),
					COLOR_OPTION("Health high", V::ESP_HealthHigh),
					COLOR_OPTION("Armour low", V::ESP_ArmourLow),
					COLOR_OPTION("Armour high", V::ESP_ArmourHigh),
					COLOR_OPTION("Occluded chams", V::Chams_OccludedColor),
					COLOR_OPTION("Unoccluded chams", V::Chams_UnoccludedColor),
					COLOR_OPTION("Health pack", V::Colors_HealthPack),
					COLOR_OPTION("Ammo pack", V::Colors_AmmoPack),
					COLOR_OPTION("Armour pack", V::Colors_ArmourPack),

				}
			}
		};

		for (size_t i = 0; i < m_ItemLists.size(); i++)
		{
			auto& ItemList = m_ItemLists.at(i);

			ItemList->m_Y = 106;

			ItemList->m_X = V::Menu_ListWidth * i;
		}

		bDone = true;
	}
}

/*CFGVAR(Menu_Text, Color_t({ 220, 220, 220, 255 }));
CFGVAR(Menu_ListWidth, int(200));
CFGVAR(Menu_ListBarH, int(30));
CFGVAR(Menu_ListBG, Color_t({ 40, 40, 40, 255 }));
CFGVAR(Menu_ListBar, Color_t({ 30, 30, 30, 255 }));
CFGVAR(Menu_ListOutline, Color_t({ 100, 100, 100, 255 }));
CFGVAR(Menu_GroupH, int(20));
CFGVAR(Menu_GroupBG, Color_t({ 35, 35, 35, 255 }));
CFGVAR(Menu_GroupHover, Color_t({ 60, 60, 60, 255 }));
CFGVAR(Menu_ItemBG, Color_t({ 80, 80, 80, 255 }));
CFGVAR(Menu_ItemHover, Color_t({ 225, 177, 44, 255 }));*/

CMenu::~CMenu()
{
	for (auto ItemList : m_ItemLists)
	{
		for (auto ItemGroup : ItemList->m_ItemGroups)
		{
			for (auto Item : ItemGroup->m_Items)
			{
				delete Item;
			}

			delete ItemGroup;
		}

		delete ItemList;
	}
}

#include "JORHOOK.h"

void CMenu::Run()
{
	CreateLists();

	if (GetAsyncKeyState(VK_INSERT) & 0x1)
	{
		m_Open = !m_Open;
		I::Surface->SetCursorAlwaysVisible(m_Open);
	}

	if (m_Open)
	{
		static bool m_bInitLogo = false;

		G::Draw.Rect(0, 0, G::ScreenSize.w, G::ScreenSize.h, { 0,0,0,180 });

		G::Draw.String(FONT_ESP, 10, 20, { 255,255,255,255 }, "JORHOOK v1.1 - Use right click to increment");
		G::Draw.String(FONT_ESP, 10, 34, { 255,255,255,255 }, "and left click to decrement values in the menu");
		G::Draw.String(FONT_ESP, 10, 48, { 255,255,255,255 }, "Build date: " __DATE__);

		static int nTextureIDOut = I::Surface->CreateNewTextureID(true);
		if (!m_bInitLogo)
		{
			I::Surface->DrawSetTextureRGBAEx(nTextureIDOut, jor_logo::rawData, 377, 106, IMAGE_FORMAT_BGRA8888);
			m_bInitLogo = true;
			return;
		}
		if (m_bInitLogo)
		{
			I::Surface->SetDrawColor(255, 255, 255, 255);
			I::Surface->DrawSetTexture(nTextureIDOut);
			I::Surface->DrawTexturedRect((G::ScreenSize.w / 2) - (377 / 2), 0, 377, 106);
		}


		InputHelper::Update();

		int x = 0, y = 0;
		I::Surface->GetCursorPos(x, y);

		for (size_t nItemList = 0; nItemList < m_ItemLists.size(); nItemList++)
		{
			CItemList* ItemList = m_ItemLists.at(nItemList);

			int posx = ItemList->m_X;
			int posy = ItemList->m_Y;

			ItemList->Drag(x, y);

			//main background
			G::Draw.Rect(posx, posy, V::Menu_ListWidth, ItemList->m_Height, V::Menu_ListBG);
			//bar
			G::Draw.Rect(posx, posy, V::Menu_ListWidth, V::Menu_ListBarH, V::Menu_ListBar);
			//name
			G::Draw.StringCenterV(FONT_MENU, (posx)+V::Menu_ListWidth / 2, posy + V::Menu_ListBarH / 2, V::Menu_Text, ItemList->m_Name.c_str());
			//outline
			G::Draw.OutlinedRect(posx, posy, V::Menu_ListWidth, ItemList->m_Height, V::Menu_ListOutline);

			int nDrawnItems = 0;

			int nLimit = posy + ItemList->m_Height;
			int nCount = 0;

			for (size_t nItemGroup = 0; nItemGroup < ItemList->m_ItemGroups.size(); nItemGroup++)
			{
				CItemGroup* ItemGroup = ItemList->m_ItemGroups.at(nItemGroup);



				int nGroupX = posx;
				int nGroupY = posy + V::Menu_ListBarH + (V::Menu_GroupH * nItemGroup) + (nDrawnItems * V::Menu_GroupH);

				while (nGroupY > nLimit)
				{
					ItemList->m_Height += V::Menu_ListBarH * 5;
					nLimit = posy + ItemList->m_Height;
				}

				bool bHovered = (x > nGroupX && x < (nGroupX + (V::Menu_ListWidth - 2)) && y > nGroupY && y < (nGroupY + V::Menu_GroupH));

				if (bHovered)
				{
					if (InputHelper::IsPressed(VK_LBUTTON))
					{
						ItemGroup->m_Open = !ItemGroup->m_Open;
					}
				}

				Color_t clr = bHovered ? V::Menu_GroupHover : V::Menu_GroupBG;

				auto font = FONT_MENU;

				if (ItemGroup->e_Type == EItemType::COLOR)
				{
					clr = bHovered ? V::Menu_GroupHover : *(reinterpret_cast<CItemClrGroup*>(ItemGroup))->m_Clr;
					if (!bHovered)
					{
						font = FONT_ESP_NAME;
					}
				}


				//main background
				G::Draw.Rect(nGroupX + 1, nGroupY, V::Menu_ListWidth - 2, V::Menu_GroupH, clr);
				//name
				G::Draw.StringCenterV(font, nGroupX + (V::Menu_ListWidth / 2) + 1, nGroupY + V::Menu_GroupH / 2, bHovered ? V::Menu_Text : Color_t{ 255, 255, 255, 255 }, ItemGroup->m_Name.c_str());

				if (ItemGroup->m_Open)
				{
					for (size_t nItems = 0; nItems < ItemGroup->m_Items.size(); nItems++)
					{
						CItemBase* Item = ItemGroup->m_Items.at(nItems);

						int nItemY = nGroupY + (V::Menu_GroupH * (nItems + 1));
						bool bHovered = (x > nGroupX && x < (nGroupX + (V::Menu_ListWidth - 2)) && y > nItemY && y < (nItemY + V::Menu_GroupH));

						int nDrawX = (nGroupX + 10);
						int nDrawValX = (nGroupX + 160);
						int nDrawY = (nItemY + (V::Menu_GroupH / 2));
						Color_t DrawCol = (bHovered ? V::Menu_ItemHover : V::Menu_Text);

						switch (Item->e_Type)
						{
							case EItemType::INT:
							{
								CItemInt* Int = reinterpret_cast<CItemInt*>(Item);

								//name
								G::Draw.StringCenterVOnly(FONT_MENU, nDrawX, nDrawY, DrawCol, "%s", Int->m_Name.c_str());

								if (!Int->m_Aliases.empty())
								{
									if (bHovered)
									{
										if (InputHelper::IsPressedAndHeld(VK_RBUTTON))
										{
											Int->m_AliasIdx++;
											Int->m_AliasIdx = std::clamp(Int->m_AliasIdx, 0, static_cast<int32_t>(Int->m_Aliases.size() - 1));
											*reinterpret_cast<int*>(Int->m_Ptr) = Int->m_Aliases.at(Int->m_AliasIdx).first;
										}

										if (InputHelper::IsPressedAndHeld(VK_LBUTTON))
										{
											Int->m_AliasIdx--;
											Int->m_AliasIdx = std::clamp(Int->m_AliasIdx, 0, static_cast<int32_t>(Int->m_Aliases.size() - 1));
											*reinterpret_cast<int*>(Int->m_Ptr) = Int->m_Aliases.at(Int->m_AliasIdx).first;
										}
									}

									//value
									G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%s", Int->m_Aliases.at(Int->m_AliasIdx).second.c_str());
								}

								else
								{
									if (bHovered)
									{
										if (InputHelper::IsPressedAndHeld(VK_RBUTTON))
										{
											*reinterpret_cast<int*>(Int->m_Ptr) += 1;
											*reinterpret_cast<int*>(Int->m_Ptr) = std::clamp(*reinterpret_cast<int*>(Int->m_Ptr), Int->m_Min, Int->m_Max);
										}

										if (InputHelper::IsPressedAndHeld(VK_LBUTTON))
										{
											*reinterpret_cast<int*>(Int->m_Ptr) -= 1;
											*reinterpret_cast<int*>(Int->m_Ptr) = std::clamp(*reinterpret_cast<int*>(Int->m_Ptr), Int->m_Min, Int->m_Max);
										}
									}

									//value
									G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%d", *reinterpret_cast<int*>(Int->m_Ptr));
								}

								break;
							}

							case EItemType::BUTTON:
							{
								CItemButton* Button = reinterpret_cast<CItemButton*>(Item);

								G::Draw.StringCenterV(FONT_MENU, (nGroupX + V::Menu_ListWidth / 2) + 1, nDrawY, DrawCol, "%s", Button->m_Name.c_str());

								float flTime = I::Engine->Time();

								float flDeltaTime = flTime - Button->m_flTimePressed;

								if (bHovered)
								{
									if (InputHelper::IsPressed(VK_LBUTTON))
									{
										if (flDeltaTime > 0.1f)
										{
											Button->m_Ptr();
											Button->m_flTimePressed = I::Engine->Time();
										}
									}
								}

								break;
							}

							case EItemType::KEY:
							{
								CItemKey* Key = reinterpret_cast<CItemKey*>(Item);

								G::Draw.StringCenterVOnly(FONT_MENU, nDrawX, nDrawY, DrawCol, "%s", Key->m_Name.c_str());

								auto key = reinterpret_cast<int*>(Key->m_Ptr);

								if (!Key->m_bActive)
								{
									if (bHovered)
									{
										if (InputHelper::IsPressed(VK_LBUTTON))
										{
											Key->m_bActive = true;
											Key->m_flTimeActivated = I::Engine->Time();
											break;
										}
									}
									else
									{
										if (InputHelper::IsPressed(VK_LBUTTON))
										{
											Key->m_bActive = false;
										}
									}
								}

								if (Key->m_bActive)
								{
									G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "Press key");

									if (InputHelper::IsPressed(VK_ESCAPE))
									{
										Key->m_bActive = false;
										break;
									}

									float flTimeDifference = I::Engine->Time() - Key->m_flTimeActivated;

									if (flTimeDifference > 0.1f)
									{
										for (short n = 0; n < 256; n++)
										{
											if ((n > 0x0 && n < 0x7) || (n > L'A' - 1 && n < L'Z' + 1) || n == VK_LSHIFT || n == VK_RSHIFT || n == VK_SHIFT || n == VK_ESCAPE || n == VK_INSERT || n == VK_MENU || n == VK_CONTROL || n == VK_SPACE)
											{
												if (InputHelper::IsPressed(n))
												{
													*key = n;
													Key->m_bActive = false;
													Key->m_flTimeActivated = 0.f;
													break;
												}
											}
										}
									}
								}
								else
								{
									G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%s", CItemKey::KeyCodeToString(*key).c_str());
								}

								break;
							}

							case EItemType::COLOR:
							{
								CItemClr* Int = reinterpret_cast<CItemClr*>(Item);

								//name
								G::Draw.StringCenterVOnly(FONT_MENU, nDrawX, nDrawY, DrawCol, "%s", Int->m_Name.c_str());

								auto clr = reinterpret_cast<Color_t*>(Int->m_Ptr);

								if (bHovered)
								{
									if (InputHelper::IsPressedAndHeld(VK_RBUTTON))
									{
										switch (Int->m_Type)
										{
											default:
											case EClrType::r:
											{
												if (clr->r != 255) { clr->r += 1; }; break;
											}
											case EClrType::g:
											{
												if (clr->g != 255) { clr->g += 1; }; break;
											}
											case EClrType::b:
											{
												if (clr->b != 255) { clr->b += 1; }; break;
											}
											case EClrType::a:
											{
												if (clr->a != 255) { clr->a += 1; }; break;
											}
										}
									}

									if (InputHelper::IsPressedAndHeld(VK_LBUTTON))
									{
										switch (Int->m_Type)
										{
											default:
											case EClrType::r:
											{
												if (clr->r != 0) { clr->r -= 1; }; break;
											}
											case EClrType::g:
											{
												if (clr->g != 0) { clr->g -= 1; }; break;
											}
											case EClrType::b:
											{
												if (clr->b != 0) { clr->b -= 1; }; break;
											}
											case EClrType::a:
											{
												if (clr->a != 0) { clr->a -= 1; }; break;
											}
										}
									}
								}

								int n = 0;

								switch (Int->m_Type)
								{
									default:
									case EClrType::r:
									{
										n = (int)clr->r; break;
									}
									case EClrType::g:
									{
										n = (int)clr->g; break;
									}
									case EClrType::b:
									{
										n = (int)clr->b; break;
									}
									case EClrType::a:
									{
										n = (int)clr->a; break;
									}
								}

								//value
								G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%d", n);


								break;
							}

							case EItemType::FLOAT:
							{
								CItemFloat* Float = reinterpret_cast<CItemFloat*>(Item);

								//name
								G::Draw.StringCenterVOnly(FONT_MENU, nDrawX, nDrawY, DrawCol, "%s", Float->m_Name.c_str());

								if (bHovered)
								{
									if (InputHelper::IsPressedAndHeld(VK_RBUTTON))
									{
										*reinterpret_cast<float*>(Float->m_Ptr) += Float->m_Step;
										*reinterpret_cast<float*>(Float->m_Ptr) = std::clamp(*reinterpret_cast<float*>(Float->m_Ptr), Float->m_Min, Float->m_Max);
									}

									if (InputHelper::IsPressedAndHeld(VK_LBUTTON))
									{
										*reinterpret_cast<float*>(Float->m_Ptr) -= Float->m_Step;
										*reinterpret_cast<float*>(Float->m_Ptr) = std::clamp(*reinterpret_cast<float*>(Float->m_Ptr), Float->m_Min, Float->m_Max);
									}
								}

								//value
								G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%.2f", *reinterpret_cast<float*>(Float->m_Ptr));

								break;
							}

							case EItemType::BOOL:
							{
								CItemBool* Bool = reinterpret_cast<CItemBool*>(Item);

								//name
								G::Draw.StringCenterVOnly(FONT_MENU, nDrawX, nDrawY, DrawCol, "%s", Bool->m_Name.c_str());

								if (bHovered && InputHelper::IsPressedAndHeld(VK_LBUTTON))
									*Bool->m_Ptr = !*Bool->m_Ptr;

								//value
								G::Draw.StringCenterV(FONT_MENU, nDrawValX, nDrawY, DrawCol, "%s", *Bool->m_Ptr ? "On" : "Off");

								break;
							}
						}
					}
				}

				if (ItemGroup->m_Open)
				{
					nDrawnItems += ItemGroup->m_Items.size();
				}
			}
		}
	}
}

void CItemList::Drag(int mousex, int mousey)
{
	bool held = InputHelper::IsHeld(VK_LBUTTON);
	if ((mousex > m_X && mousex < m_X + V::Menu_ListWidth && mousey > m_Y && mousey < m_Y + V::Menu_ListBarH) && held)
	{
		m_bDrag = true;

		if (!m_bMove)
		{
			m_Delta.x = mousex - m_X;
			m_Delta.y = mousey - m_Y;
			m_bMove = true;
		}
	}

	if (m_bDrag)
	{
		m_X = mousex - m_Delta.x;
		m_Y = mousey - m_Delta.y;
	}

	if (!held)
	{
		m_bDrag = false;
		m_bMove = false;
	}
}
