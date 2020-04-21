#include "HelloBoulderLayer.h"
#include "Boulder.h"
#include "Diamond.h"
#include "Player.h"

#include "Hazel/Core/KeyCodes.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Renderer/RenderCommand.h"
#include "Hazel/Renderer/Renderer2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iomanip>
#include <sstream>

#ifdef _DEBUG
#include <imgui.h>
#endif

static std::vector<LevelDefinition> levelDefinition = {
	{ 40, 22, 12, 150,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"W...... ..d.r .....r.r....... ....r....W"
	"W.rPr...... .........rd..r.... ..... ..W"
	"W.......... ..r.....r.r..r........r....W"
	"Wr.rr.........r......r..r....r...r.....W"
	"Wr. r......... r..r........r......r.rr.W"
	"W... ..r........r.....r. r........r.rr.W"
	"Wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww...r..r.W"
	"W. ...r..d. ..r.r..........d.rd...... .W"
	"W..d.....r..... ........rr r..r....r...W"
	"W...r..r.r..............r .r..r........W"
	"W.r.....r........rrr.......r.. .d....r.W"
	"W.d.. ..r.  .....r.rd..d....r...r..d. .W"
	"W. r..............r r..r........d.....rW"
	"W........wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwW"
	"W r.........r...d....r.....r...r.......W"
	"W r......... r..r........r......r.rr..XW"
	"W. ..r........r.....r.  ....d...r.rr...W"
	"W....rd..r........r......r.rd......r...W"
	"W... ..r. ..r.rr.........r.rd...... ..rW"
	"W.d.... ..... ......... .r..r....r...r.W"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	},
	{40, 22, 10, 150,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"W.r..r..w.r...d.w... .r.wr......w..rr..W"
	"W.......w......rwrr. ...w ..d...w....r.W"
	"W                                      W"
	"Wd......w.r....rw.r. .. w..r..d.w..r.r.W"
	"W.......w.r....rw.r. r..w.....r.w... ..W"
	"Wwwwwwwwwwwwwwwwwwww wwwwwwwwwwwwwwwwwwW"
	"W....rr.w..r....w... ..rw....r..w.....rW"
	"W.......w.. ....w... ...w....r. w.....rW"
	"W                                      W"
	"Wr..r...w....r..w..r ...w......dwr.....W"
	"Wr....r.w..r..r.w... . rw.......wr...r.W"
	"W.r.....w...r...w... . rw.......w r..r.W"
	"Wwwwwwwwwwwwwwwwwwww wwwwwwwwwwwwwwwwwwW"
	"Wr.  q..w....r.rw... ...w.rd..r.w......W"
	"W.....r.wr......w..d ...w ..r...w.r.rr.W"
	"W                                      W"
	"Wd.. .r.wr....r.w.r. ..rw.r.r...w......W"
	"W.....r.wr..d...w... r..w..r....w...rr W"
	"W.d... rw..r....w.Pd r..w. .....w...rr W"
	"W.r.... w.. ..r.w.X. ...w....r.rw.... .W"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	},
	{40, 22, 24, 150,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"Wr.ww.wrr.w...rwr..r....w...r.....rw.d.W"
	"W..Xw.d.r.w...www..w.r....r..r.r...w.wrW"
	"W....w..rd..r....w.....r.wwr.......w.wwW"
	"Wd.w..wrwr..r....w...r......r.rr......wW"
	"Wr.w...w..r.ww..r.wwd.......r.rr......wW"
	"Wrr..r....w...r......r.rr......r..dww..W"
	"W..r.ww..r.rr...w....r.rr......w..r.w.rW"
	"W..w...d......d.r..wwr..r.w.wr..wr..d.rW"
	"Wr.r....w.ww..d.r..wwr..r..d.w...w..r.wW"
	"W.r.ww.....rrwr..d.w.wr..wr...wr..d.r..W"
	"Ww.ww......rrwr..r.w.ww...w..r.ww..r.wwW"
	"W.w.r.r.w...wwr..r....w...r.....ww.r.wwW"
	"W.w.r.r.w.d.w.wr..wr....r..r.rr....w...W"
	"Ww..wrwr..r....w...d...w.rw......w.ww.dW"
	"Ww...wwr..w.d...wr..r.r...r.wr......w..W"
	"Ww.d....r.ww..r.wwr.......r.wr......w..P"
	"W..r....w...r......r.rr......w..r.w...wW"
	"Wr.ww..r.ww...w....r.rr......w..rd..r..W"
	"Ww...r......r.rd......r...ww..wr..d.w..W"
	"Wrr...w.....r.rd......w..r.wd.d.rw.r...W"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	},
	{40, 22, 36, 120,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WP.....r....................r........r.W"
	"W.....r..............r.................W"
	"W........r..r..........................W"
	"Wr.....................................W"
	"W...................r..................W"
	"W.r.....................r.........r....W"
	"W..r.....r...........r..r.............rW"
	"W......r......r.....................r..W"
	"W........ B...r.. B...... B...... B....W"
	"W........  ...r..  ......  ......  .r..W"
	"W......................................W"
	"W...r..............................r...W"
	"W...r.....r............................W"
	"W......r...........r..................rW"
	"W...........r.......r..................W"
	"W..r..............r....................W"
	"W.....................r.........r......W"
	"W................................r..r..W"
	"W....r......r.rr..................r....W"
	"W...........r.rr.........r..r.r.......XW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	},
	{ 40, 22, 6, 120,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WP.....................................W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W.......  F.....  F.....  F.....  F....W"
	"W.......   .....   .....   .....   ....W"
	"W....... d ..... d ..... d ..... d ....W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W.......  F.....  F.....  F.....  F....W"
	"W.......   .....   .....   .....   ....W"
	"W....... d ..... d ..... d ..... d ....W"
	"W......................................W"
	"W......................................W"
	"W......................................W"
	"W.....................................XW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	},
	{ 40, 22, 10, 0,
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWW  WWWWWW  W        WW  WWWW  WWWWW"
	"WWWWWWW  WWWW PWW  WWWW  WW  WWWW  WWWWW"
	"WWWWWWWW  WW  WWW  WWWW  WW  WWWW  WWWWW"
	"WWWWWWWWWW  WWWWW  WWWW  WW  WWWW  WWWWW"
	"WWWWWWWWWW  WWWWW  WWWW  WW  WWWW  WWWWW"
	"WWWWWWWWWW  WWWWW        WWW      WWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWW  WWWWWW  WW      WWW  WWW  WWWWWWWW"
	"WWWW  WWWWWW  WWWW  WWWWW   WW  WWWWWWWW"
	"WWWWW  WWWW  WWWWW  WWWWW    W  WWWWWWWW"
	"WWWWW  W  W  WWWWW  WWWWW  W    WWWWWWWW"
	"WWWWWW      WWWWWW  WWWWW  WW   WWWWWWWW"
	"WWWWWW  WW  WWWW      WWW  WWW  WWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
	}
};

HelloBoulderLayer::HelloBoulderLayer()
: Layer("HelloBoulder")
, m_FixedTimestep(0.125)
, m_ViewPort(0.0f, 0.0f, 20.0f, 10.0f)
, m_TileSize(1.0f, 1.0f)
, m_AccumulatedTs(0.0f)
, m_PlayerIsAlive(false)
, m_GamePaused(false)
, m_CurrentLevel(4)
, m_WonLevel(false)
{
	m_ViewPort.SetCameraSpeed((1.0f / m_FixedTimestep) - 1.0f);
}

void HelloBoulderLayer::OnAttach() {
	// Load tiles
	std::string basePath = "assets/textures/tile";
	std::string extension = ".png";

	for (size_t i = 0; i < m_Tiles.size(); ++i) {
		std::ostringstream os;
		os << std::setfill('0') << std::setw(3) << i;
		std::string path = basePath + os.str() + extension;
		m_Tiles[i] = Hazel::Texture2D::Create(path);
	}

	// Load level
	LoadLevel(m_CurrentLevel);
}

void HelloBoulderLayer::OnDetach() {
}

void HelloBoulderLayer::OnUpdate(Hazel::Timestep ts) {

	if (m_GamePaused) {
		return;
	}

	if (m_WonLevel) {
		LoadLevel(++m_CurrentLevel);
	}

	// Update game level on fixed timestep
	m_AccumulatedTs += ts;
	if (m_AccumulatedTs > m_FixedTimestep) {
		m_Level.ClearUpdated();
		for (size_t row = 0; row < m_Level.GetHeight(); ++row) {
			for (size_t col = 0; col < m_Level.GetWidth(); ++col) {
				
				// the "physics" work better if we go from top down.
				size_t flipRow = m_Level.GetHeight() - (row + 1);
				if(!m_Level.IsUpdated(flipRow, col)) {
					m_Level.GetGameObject(flipRow, col).FixedUpdate(flipRow, col, m_Level);
				}
			}
		}
		m_AccumulatedTs = 0.0;
	}

	// Animate
	for (size_t row = 0; row < m_Level.GetHeight(); ++row) {
		for (size_t col = 0; col < m_Level.GetWidth(); ++col) {
			m_Level.GetGameObject(row, col).Animate(ts);
		}
	}

	m_ViewPort.Update(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1});
	Hazel::RenderCommand::Clear();
	Hazel::Renderer2D::BeginScene(m_ViewPort.GetCamera());

	size_t minRow = std::max((size_t)0, (size_t)std::floor(m_ViewPort.GetBottom()));
	size_t maxRow = std::min(m_Level.GetHeight(), (size_t)std::ceil(m_ViewPort.GetTop()));
	size_t minCol = std::max((size_t)0, (size_t)std::floor(m_ViewPort.GetLeft()));
	size_t maxCol = std::min(m_Level.GetWidth(), (size_t)std::ceil(m_ViewPort.GetRight()));

	m_PlayerIsAlive = false;
	for (size_t row = minRow; row < maxRow; ++row) {
		for (size_t col = minCol; col < maxCol; ++col) {
			GameObject& object = m_Level.GetGameObject(row, col);
			if (!object.IsEmpty()) {
				glm::vec3 position(col - m_ViewPort.GetLeft() + 0.5f, row - m_ViewPort.GetBottom() + 0.5f, 0.0f);
				Hazel::Renderer2D::DrawQuad(position, m_TileSize, m_Tiles[(int)object.GetTile()]);
				if (object.IsPlayer()) {
					m_ViewPort.SetPlayerPosition((float)col, (float)row);
					m_PlayerIsAlive = true;
					if ((row == m_Level.GetExitRow()) && (col == m_Level.GetExitCol())) {
						m_WonLevel = true;
					}
				}
			}
		}
	}

	Hazel::Renderer2D::EndScene();
}

void HelloBoulderLayer::OnEvent(Hazel::Event& e) {
	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(HelloBoulderLayer::OnKeyPressed));
}


bool HelloBoulderLayer::OnKeyPressed(Hazel::KeyPressedEvent& e) {
	if (e.GetKeyCode() == HZ_KEY_SPACE) {
		if (m_PlayerIsAlive) {
			m_GamePaused = !m_GamePaused;
		} else {
			LoadLevel(m_CurrentLevel);
		}
	} else if (e.GetKeyCode() == HZ_KEY_ESCAPE) {
		LoadLevel(m_CurrentLevel);
	}
	return true;
}


void HelloBoulderLayer::LoadLevel(int level) {
	m_Level.Init(levelDefinition[level]);
	m_WonLevel = false;
	m_ViewPort.SetLevelSize((float)m_Level.GetWidth(), (float)m_Level.GetHeight());
	m_ViewPort.SetPlayerPosition((float)m_Level.GetPlayerInitialCol(), (float)m_Level.GetPlayerInitialRow());
}

#ifdef _DEBUG
void HelloBoulderLayer::OnImGuiRender() {
	int updateFPS = (int)(1.0f / m_FixedTimestep);
	ImGui::Begin("Game Settings");
	ImGui::Text("Score: %d", m_Level.GetScore());
	ImGui::DragInt("Movement FPS", &updateFPS, 1, 1, 60);
	ImGui::End();
	m_FixedTimestep = 1.0f / updateFPS;
	m_ViewPort.SetCameraSpeed((1.0f / m_FixedTimestep) - 1.0f);

	for (size_t row = 0; row < m_Level.GetHeight(); ++row) {
		for (size_t col = 0; col < m_Level.GetWidth(); ++col) {
			if (m_Level.GetGameObject(row, col).IsPlayer()) {
				m_Level.GetGameObject(row, col).ImGuiRender();
			}
		}
	}
}
#endif

