/*************************************************************************
[ÎÄ¼þÃû]           dialogbase.h
[¹¦ÄÜÄ£¿éºÍÄ¿µÄ]   ´ËÀàÓÃÓÚËùÓÐ¶¨ÖÆ¶Ô»°¿òµÄ»ùÀà£¬
                   ¹¦ÄÜ°üÀ¨Ä¬ÈÏÃ»ÓÐ±ß¿ò£¬Í¸Ã÷¶ÈÎª0.7£¬¿ÉÒÆ¶¯
[¿ª·¢Õß¼°ÈÕÆÚ]     lyk 2014-09-09
[°æ±¾]             v1.0
[¸ü¸Ä¼ÇÂ¼]
*************************************************************************/

#ifndef DIALOGBASE_H
#define DIALOGBASE_H

#include <QDialog>
#include <QMouseEvent>
#include <QLayout>
#include <QGridLayout>

#define PADDING 4
#ifdef utils_EXPORTS
#define UTILS_EX __declspec(dllexport)
#else
#define UTILS_EX __declspec(dllimport)
#endif

class UTILS_EX DialogBase : public QDialog
{
	Q_OBJECT

public:
	DialogBase( QWidget *parent=0);
	~DialogBase();
	enum Direction 
	{ 
		UP = 0, 
		DOWN = 1, 
		LEFT, 
		RIGHT, 
		LEFTTOP, 
		LEFTBOTTOM, 
		RIGHTBOTTOM, 
		RIGHTTOP, 
		NONE
	};
	void setMoveEanable(bool isMove = true);
protected:
	virtual void mousePressEvent(QMouseEvent* e);
	virtual void mouseMoveEvent(QMouseEvent* e);
	virtual void mouseReleaseEvent(QMouseEvent* e);
	virtual void leaveEvent(QEvent *);

private:
	bool m_bIsWindowMoveable;
	QPoint m_dragPoint;

private:
	void region(const QPoint &cursorGlobalPoint);

	bool m_bIsMove;
	bool isLeftPressDown;  
	QPoint dragPosition;   
	Direction dir;
};

#endif // DIALOGBASE_H
