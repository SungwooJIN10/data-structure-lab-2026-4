#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMap>
#include <QVector>
#include <QQueue>
#include <QString>
#include <QStringList>

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("서울 지하철 최단 경로 찾기");
        resize(700, 680);

        QWidget* central = new QWidget(this);
        setCentralWidget(central);

        QVBoxLayout* mainLayout = new QVBoxLayout(central);

        QLabel* title = new QLabel("<h2>서울 지하철 최단 경로 찾기</h2>");
        title->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(title);

        QLabel* explain = new QLabel(
            "지하철역을 노드(Node), 역 사이 연결을 간선(Edge)으로 저장하고 "
            "BFS 알고리즘으로 최단 경로를 찾는 프로그램입니다."
        );
        explain->setWordWrap(true);
        explain->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(explain);

        QLabel* imageLabel = new QLabel;
        QPixmap pixmap("데이터구조 프로젝트.png");

        if (pixmap.isNull()) {
            imageLabel->setText("<h3 style='color:red'>이미지 로드 실패</h3>");
        } else {
            imageLabel->setPixmap(
                pixmap.scaled(620, 350, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            );
        }

        imageLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(imageLabel);

        QHBoxLayout* selectLayout = new QHBoxLayout;

        startBox = new QComboBox;
        endBox = new QComboBox;

        selectLayout->addWidget(new QLabel("출발역"));
        selectLayout->addWidget(startBox);
        selectLayout->addWidget(new QLabel("도착역"));
        selectLayout->addWidget(endBox);

        mainLayout->addLayout(selectLayout);

        QPushButton* searchButton = new QPushButton("최단 경로 찾기");
        mainLayout->addWidget(searchButton);

        resultBox = new QTextEdit;
        resultBox->setReadOnly(true);
        mainLayout->addWidget(resultBox);

        makeGraph();

        QStringList stations = graph.keys();
        startBox->addItems(stations);
        endBox->addItems(stations);

        connect(searchButton, &QPushButton::clicked, this, [this]() {
            findShortestPath();
        });
    }

private:
    QComboBox* startBox;
    QComboBox* endBox;
    QTextEdit* resultBox;

    QMap<QString, QVector<QString>> graph;

    void addEdge(QString a, QString b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void makeGraph() {
        addEdge("서울역", "시청");
        addEdge("시청", "종각");
        addEdge("종각", "종로3가");
        addEdge("종로3가", "동대문");
        addEdge("동대문", "동대문역사문화공원");

        addEdge("시청", "을지로입구");
        addEdge("을지로입구", "을지로3가");
        addEdge("을지로3가", "을지로4가");
        addEdge("을지로4가", "동대문역사문화공원");

        addEdge("서울역", "충정로");
        addEdge("충정로", "아현");
        addEdge("아현", "이대");
        addEdge("이대", "신촌");
        addEdge("신촌", "홍대입구");

        addEdge("홍대입구", "합정");
        addEdge("합정", "당산");
        addEdge("당산", "영등포구청");

        addEdge("종로3가", "충무로");
        addEdge("충무로", "명동");
        addEdge("명동", "회현");
        addEdge("회현", "서울역");
    }

    void findShortestPath() {
        QString start = startBox->currentText();
        QString end = endBox->currentText();

        if (start == end) {
            resultBox->setText(
                "출발역과 도착역이 같습니다.\n\n"
                "경로: " + start +
                "\n이동 횟수: 0"
                "\n예상 소요 시간: 0분"
            );
            return;
        }

        QQueue<QString> queue;
        QMap<QString, bool> visited;
        QMap<QString, QString> parent;

        queue.enqueue(start);
        visited[start] = true;

        while (!queue.isEmpty()) {
            QString current = queue.dequeue();

            for (QString next : graph[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = current;
                    queue.enqueue(next);

                    if (next == end) {
                        queue.clear();
                        break;
                    }
                }
            }
        }

        if (!visited[end]) {
            resultBox->setText("경로를 찾을 수 없습니다.");
            return;
        }

        QStringList path;
        QString current = end;

        while (current != start) {
            path.prepend(current);
            current = parent[current];
        }

        path.prepend(start);

        int moveCount = path.size() - 1;
        int travelTime = moveCount * 2;

        resultBox->setText(
            "최단 경로\n" +
            path.join(" → ") +
            "\n\n이동 횟수: " + QString::number(moveCount) +
            "\n예상 소요 시간: " + QString::number(travelTime) + "분"
        );
    }
};