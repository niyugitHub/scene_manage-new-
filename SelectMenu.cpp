#include"SelectMenu.h"
#include"Dxlib.h"

namespace
{
	// メニュー項目の間隔
	constexpr int kMenuItemInterval = 32;
}

// =======================================
// SelectMenu::Item
// =======================================

SelectMenu::Item::Item()
{
	m_text = nullptr;
}

SelectMenu::Item::~Item()
{

}

void SelectMenu::Item::draw(int x, int y)
{
	DrawString(x, y, m_text, GetColor(255, 255, 255));
}

int SelectMenu::Item::getTextWidth()
{
	return GetDrawStringWidth(m_text, strlen(m_text));
}

void SelectMenu::Item::setText(const char* text)
{
	m_text = text;
}

// =======================================
// SelectMenu::Cursor
// =======================================
SelectMenu::Cursor::Cursor()
{
	m_selectIndex = 0;
	m_itemNum = 4;
}

SelectMenu::Cursor::~Cursor()
{

}

void SelectMenu::Cursor::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (padState & PAD_INPUT_UP)
		{
			m_selectIndex--;
			// 上下ループ
			if (m_selectIndex < 0)
			{
				m_selectIndex = m_itemNum - 1;
			}
		}
		if (padState & PAD_INPUT_DOWN)
		{
			m_selectIndex++;
			// 上下ループ
			if (m_selectIndex > m_itemNum - 1)
			{
				m_selectIndex = 0;
			}
		}
}

void SelectMenu::Cursor::draw()
{
	int posX = m_menuPos.x;
	int posY = m_menuPos.y + kMenuItemInterval * m_selectIndex;

	DrawBox(posX, posY, posX + m_size.x, posY + m_size.y, GetColor(255, 0, 0), false);
}

// =======================================
// SelectMenu
// =======================================

SelectMenu::SelectMenu()
{

}

SelectMenu::~SelectMenu()
{

}

void SelectMenu::init()
{
	
}

void SelectMenu::end()
{
	for (auto& pItem : m_pItem)
	{
		delete pItem;
	}
	m_pItem.clear();
}

void SelectMenu::update()
{
	m_cursor.update();
}

void SelectMenu::draw()
{
	int width = 0;
	int height = kMenuItemInterval * m_pItem.size();

	
	DrawBox(m_pos.x, m_pos.y, 128, 128, GetColor(64, 64, 64), true);
	for (int i = 0; i < m_pItem.size(); i++)
	{
		m_pItem[i]->draw(m_pos.x,m_pos.y + i * kMenuItemInterval);
	}
	m_cursor.draw();
}

void SelectMenu::setupCursor()
{
	m_cursor.setMenuPos(m_pos);
	m_cursor.setSize(Vec2(getWindouWidth(),kMenuItemInterval));
	
}

void SelectMenu::setPos(float x, float y)
{
	setPos(Vec2(x, y));
}

void SelectMenu::setPos(Vec2 pos)
{
	m_pos = pos;
}

void SelectMenu::addItem(const char* text)
{
	Item* pItem = new Item;
	pItem->setText(text);
	m_pItem.push_back(pItem);
}

int SelectMenu::getWindouWidth()
{
	int width = 0;

	// 一番横幅の広いメニュー項目の幅をウインドウサイズにする
	for (auto& pItem : m_pItem)
	{
		if (width < pItem->getTextWidth())
		{
			width = pItem->getTextWidth();
		}
	}
	return width;
}

int SelectMenu::getWindouHeight()
{
	return kMenuItemInterval * m_pItem.size();
}
