#include "DialogBase.h"
#include <QSpacerItem>
#include <QApplication>

DialogBase::DialogBase(QWidget *parent)
	: QDialog(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	//setAttribute(Qt::WA_TranslucentBackground);
	setWindowOpacity(0.9);
	m_bIsWindowMoveable = false;
	m_dragPoint = QPoint(0, 0);
	m_bIsMove = true;
	//可变大小
	isLeftPressDown = false;
	this->dir = NONE;
	this->setMouseTracking(true); // 追踪鼠标
}

DialogBase::~DialogBase()
{

}

void DialogBase::mousePressEvent(QMouseEvent* e)
{
	if (e->button() ==  Qt::LeftButton)
	{
		m_bIsWindowMoveable = true;
		m_dragPoint = e->globalPos() - this->pos();

		//可变大小
		isLeftPressDown = true;
		if (dir != NONE) {
			this->mouseGrabber();
		}
		else {
			dragPosition = e->globalPos() - this->frameGeometry().topLeft();
		}
	}
	else
	{
		QDialog::mousePressEvent(e);
	}
}

void DialogBase::mouseMoveEvent(QMouseEvent* e)
{
	if (m_bIsWindowMoveable && dir == NONE && m_bIsMove)
	{
		move(e->globalPos() - m_dragPoint);
	}

	//可变大小
	QPoint gloPoint = e->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (!isLeftPressDown) {
		this->region(gloPoint);
	}
	else {

		if (dir != NONE) {
			QRect rMove(tl, rb);

			switch (dir) {
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else {
			if (m_bIsMove)
			{
				move(e->globalPos() - dragPosition);
			}	
			e->accept();
		}
	}
	QDialog::mouseMoveEvent(e);
}

void DialogBase::mouseReleaseEvent(QMouseEvent* e)
{
	m_bIsWindowMoveable = false;

	//可变大小
	if (e->button() == Qt::LeftButton) {
		isLeftPressDown = false;
		if (dir != NONE) {
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}

	QDialog::mouseReleaseEvent(e);
}

void DialogBase::region(const QPoint &cursorGlobalPoint)
{
	// 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
		// 左上角
		dir = LEFTTOP;
		QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
		//this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		// 右下角
		dir = RIGHTBOTTOM;
		QApplication::setOverrideCursor(Qt::SizeFDiagCursor);
		//this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		//左下角
		dir = LEFTBOTTOM;
		QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
		//this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
		// 右上角
		dir = RIGHTTOP;
		QApplication::setOverrideCursor(Qt::SizeBDiagCursor);
		//this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x()) {
		// 左边
		dir = LEFT;
		QApplication::setOverrideCursor(Qt::SizeHorCursor);
		//this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING) {
		// 右边
		dir = RIGHT;
		QApplication::setOverrideCursor(Qt::SizeHorCursor);
		//this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING){
		// 上边
		dir = UP;
		QApplication::setOverrideCursor(Qt::SizeVerCursor);
		//this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING) {
		// 下边
		dir = DOWN;
		QApplication::setOverrideCursor(Qt::SizeVerCursor);
		//this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// 默认
		dir = NONE;
		QApplication::setOverrideCursor(Qt::ArrowCursor);
		//this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void DialogBase::setMoveEanable(bool isMove /*= true*/)
{
	m_bIsMove = isMove;
}

void DialogBase::leaveEvent(QEvent *)
{
	dir = NONE;
	QApplication::setOverrideCursor(Qt::ArrowCursor);
}
