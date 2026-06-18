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

/*
 * MainWindow 클래스
 * - Qt의 QMainWindow를 상속받아 GUI 창을 구성합니다.
 * - 지하철 노선 데이터를 그래프 자료구조로 저장합니다.
 * - BFS 알고리즘을 이용하여 출발역과 도착역 사이의 최단 경로를 탐색합니다.
 */
class MainWindow : public QMainWindow {
public:
    /*
     * 생성자
     * - 프로그램 제목, 크기, 레이아웃을 설정합니다.
     * - 이미지, 역 선택 박스, 버튼, 결과 출력창을 생성합니다.
     * - 지하철 그래프를 초기화하고 버튼 클릭 이벤트를 연결합니다.
     */
    MainWindow() {
        setWindowTitle("서울 지하철 최단 경로 찾기");
        resize(700, 680);

        // 중앙 위젯과 전체 세로 레이아웃 생성
        QWidget* central = new QWidget(this);
        setCentralWidget(central);

        QVBoxLayout* mainLayout = new QVBoxLayout(central);

        // 프로그램 제목 출력
        QLabel* title = new QLabel("<h2>서울 지하철 최단 경로 찾기</h2>");
        title->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(title);

        // 프로그램 설명 출력
        QLabel* explain = new QLabel(
            "지하철역을 노드(Node), 역 사이 연결을 간선(Edge)으로 저장하고 "
            "BFS 알고리즘으로 최단 경로를 찾는 프로그램입니다."
        );
        explain->setWordWrap(true);
        explain->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(explain);

        // 지하철 노선도 이미지 출력
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

        // 출발역과 도착역 선택 영역 생성
        QHBoxLayout* selectLayout = new QHBoxLayout;

        startBox = new QComboBox;
        endBox = new QComboBox;

        selectLayout->addWidget(new QLabel("출발역"));
        selectLayout->addWidget(startBox);
        selectLayout->addWidget(new QLabel("도착역"));
        selectLayout->addWidget(endBox);

        mainLayout->addLayout(selectLayout);

        // 최단 경로 탐색 버튼 생성
        QPushButton* searchButton = new QPushButton("최단 경로 찾기");
        mainLayout->addWidget(searchButton);

        // 탐색 결과 출력창 생성
        resultBox = new QTextEdit;
        resultBox->setReadOnly(true);
        mainLayout->addWidget(resultBox);

        // 지하철 노선 그래프 생성
        makeGraph();

        // 그래프에 저장된 역 이름을 콤보박스에 추가
        QStringList stations = graph.keys();
        startBox->addItems(stations);
        endBox->addItems(stations);

        // 버튼 클릭 시 BFS 최단 경로 탐색 함수 실행
        connect(searchButton, &QPushButton::clicked, this, [this]() {
            findShortestPath();
        });
    }

private:
    // 출발역 선택 콤보박스
    QComboBox* startBox;

    // 도착역 선택 콤보박스
    QComboBox* endBox;

    // 최단 경로 결과 출력창
    QTextEdit* resultBox;

    /*
     * 그래프 자료구조
     * Key   : 역 이름
     * Value : 해당 역과 직접 연결된 인접 역 목록
     */
    QMap<QString, QVector<QString>> graph;

    /*
     * 두 역 사이의 간선을 추가하는 함수
     * 지하철은 양방향 이동이 가능하므로 양쪽 방향 모두 저장합니다.
     */
    void addEdge(QString a, QString b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    /*
     * 지하철 노선 데이터를 그래프에 저장하는 함수
     * 각 addEdge 호출은 두 역이 서로 연결되어 있음을 의미합니다.
     */
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

    /*
     * BFS 알고리즘을 이용하여 최단 경로를 탐색하는 함수
     * 출발역에서 가까운 역부터 차례대로 탐색하여
     * 가중치가 없는 그래프에서 가장 적은 이동 횟수의 경로를 찾습니다.
     */
    void findShortestPath() {
        QString start = startBox->currentText();
        QString end = endBox->currentText();

        // 출발역과 도착역이 같은 경우 별도 처리
        if (start == end) {
            resultBox->setText(
                "출발역과 도착역이 같습니다.\n\n"
                "경로: " + start +
                "\n이동 횟수: 0"
                "\n예상 소요 시간: 0분"
            );
            return;
        }

        // BFS 탐색에 사용할 큐
        QQueue<QString> queue;

        // 각 역의 방문 여부 저장
        QMap<QString, bool> visited;

        // 최단 경로 복원을 위해 각 역의 이전 역 저장
        QMap<QString, QString> parent;

        // 출발역부터 탐색 시작
        queue.enqueue(start);
        visited[start] = true;

        // 큐가 빌 때까지 BFS 탐색 수행
        while (!queue.isEmpty()) {
            QString current = queue.dequeue();

            // 현재 역과 연결된 인접 역들을 확인
            for (QString next : graph[current]) {
                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = current;
                    queue.enqueue(next);

                    // 도착역을 찾으면 탐색 종료
                    if (next == end) {
                        queue.clear();
                        break;
                    }
                }
            }
        }

        // 도착역을 방문하지 못한 경우 경로가 없는 것으로 처리
        if (!visited[end]) {
            resultBox->setText("경로를 찾을 수 없습니다.");
            return;
        }

        // parent 정보를 이용하여 도착역부터 출발역까지 역순으로 경로 복원
        QStringList path;
        QString current = end;

        while (current != start) {
            path.prepend(current);
            current = parent[current];
        }

        path.prepend(start);

        // 이동 횟수와 예상 소요 시간 계산
        int moveCount = path.size() - 1;
        int travelTime = moveCount * 2;   // 역 1개 이동당 2분으로 가정

        // 최종 결과 출력
        resultBox->setText(
            "최단 경로\n" +
            path.join(" → ") +
            "\n\n이동 횟수: " + QString::number(moveCount) +
            "\n예상 소요 시간: " + QString::number(travelTime) + "분"
        );
    }
};