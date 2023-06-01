#include <QtWidgets>

constexpr int MIN_RANGE = 0;
constexpr int MAX_RANGE = 150;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    auto window = new QWidget;
    window->setWindowTitle("Slider program");

    auto spinBox = new QSpinBox;
    spinBox->setRange(MIN_RANGE, MAX_RANGE);

    auto horizonSlider = new QSlider(Qt::Horizontal);
    horizonSlider->setRange(MIN_RANGE, MAX_RANGE);

    auto verticSlider = new QSlider(Qt::Vertical);
    verticSlider->setRange(MIN_RANGE, MAX_RANGE);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizonSlider, SLOT(setValue(int)));
    QObject::connect(horizonSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), verticSlider, SLOT(setValue(int)));
    QObject::connect(verticSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

    spinBox->setValue(50);

    auto button = new QPushButton("Close");
    QObject::connect(button, &QPushButton::clicked, &a, &QApplication::quit);

    auto vLayout = new QHBoxLayout;
    vLayout->addWidget(spinBox);
    vLayout->addWidget(horizonSlider);
    vLayout->addWidget(verticSlider);
    vLayout->addWidget(button);

    window->setLayout(vLayout);

    window->show();
    return a.exec();
}
