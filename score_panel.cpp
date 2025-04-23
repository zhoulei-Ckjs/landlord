#include "score_panel.h"
#include "ui_score_panel.h"

ScorePanel::ScorePanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScorePanel)
{
    ui->setupUi(this);
}

ScorePanel::~ScorePanel()
{
    delete ui;
}

void ScorePanel::SetScores(int left, int right, int user)
{
    ui->left_score_->setText(QString::number(left));
    ui->right_score_->setText(QString::number(right));
    ui->user_score_->setText(QString::number(user));
}
