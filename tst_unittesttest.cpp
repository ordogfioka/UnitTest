#include <QString>
#include <QDebug>
#include <QtTest>
#include "../Szakdolgozat/Model/graph.h"
#include "../Szakdolgozat/Model/model.h"
#include "../Szakdolgozat/Model/layout.h"
class UnitTestTest : public QObject
{
    Q_OBJECT

public:
    UnitTestTest();


private Q_SLOTS:
    void initTestCase();
    void structuralSimilarity();
    void isCore();
    void addEdge();
    void noMultipleEdge();
    void clusterize();
    void layout();
private:
    Graph graph,*resultGraph,*mainCluster;
    QVector<Graph*> graphs;
};

UnitTestTest::UnitTestTest()
{
    graph.loadFromFile("../UnitTest/graph.txt");
}

/**
 * @brief UnitTestTest::initTestCase
 * Tests the initialization of the graph
 */
void UnitTestTest::initTestCase()
{
    QVERIFY(6 == graph.getVertexes().size());
    QVERIFY(graph.getEdges()[0].size()==3);
    QVERIFY(graph.getEdges()[1].size()==2);
    QVERIFY(graph.getEdges()[2].size()==2);
    QVERIFY(graph.getEdges()[3].size()==3);
    QVERIFY(graph.getEdges()[4].size()==3);
    QVERIFY(graph.getEdges()[5].size()==3);
}

/**
 * @brief UnitTestTest::structuralSimilarity
 * Tests the struturalSimilaríty
 */
void UnitTestTest::structuralSimilarity()
{
    QVERIFY(0.5==graph.structuralSimilarity(1,2));
    QVERIFY(1==graph.structuralSimilarity(4,5));
    QVERIFY(0==graph.structuralSimilarity(1,5));
}
/**
 * @brief UnitTestTest::isCore
 * Tests the isCore function
 */
void UnitTestTest::isCore()
{
    for(int i=0;i<=5;i++)
        QVERIFY((i>2) == graph.isCore(i,0.9,2));
}
/**
 * @brief UnitTestTest::addEdge
 * Tests if new wdge is added
 */
void UnitTestTest::addEdge()
{
    QVERIFY(2 == graph.getEdges()[1].size());
    QVERIFY(2 == graph.getEdges()[2].size());
    graph.addEdge(1,2);
    QVERIFY(3 == graph.getEdges()[1].size());
    QVERIFY(3 == graph.getEdges()[2].size());
}
/**
 * @brief UnitTestTest::noMultipleEdge
 * Tests the addEdge() method to not add new edge if exist
 */
void UnitTestTest::noMultipleEdge()
{
    QVERIFY(3 == graph.getEdges()[1].size());
    QVERIFY(3 == graph.getEdges()[2].size());
    graph.addEdge(1,2);
    QVERIFY(3 == graph.getEdges()[1].size());
    QVERIFY(3 == graph.getEdges()[2].size());
}
/**
 * @brief UnitTestTest::clusterize
 * Tests the clusterize() method of the graph
 * Also tests created new graph
 * Also tests the creted hierarhy
 */
void UnitTestTest::clusterize()
{
    int max=0,value=2;
    resultGraph = graph.clusterize(0.5,2,max,value);

    QVERIFY(resultGraph->getEdges().size() == 2);
    QVERIFY(resultGraph->getVertexes().size() == 2);
    QVERIFY(((Cluster*)resultGraph->getVertexes()[0])->getChildrenID().size()==3);
    QVERIFY(((Cluster*)resultGraph->getVertexes()[1])->getChildrenID().size()==3);
    //first cluster
    QVERIFY(((Cluster*)resultGraph->getVertexes()[0])->getChildrenID().contains(0));
    QVERIFY(((Cluster*)resultGraph->getVertexes()[0])->getChildrenID().contains(1));
    QVERIFY(((Cluster*)resultGraph->getVertexes()[0])->getChildrenID().contains(2));
    //second claster
    QVERIFY(((Cluster*)resultGraph->getVertexes()[1])->getChildrenID().contains(3));
    QVERIFY(((Cluster*)resultGraph->getVertexes()[1])->getChildrenID().contains(4));
    QVERIFY(((Cluster*)resultGraph->getVertexes()[1])->getChildrenID().contains(5));

    mainCluster = resultGraph->clusterize(0.5,2,max,value);

    QVERIFY(mainCluster->getVertexes().size() == 1);
    QVERIFY(mainCluster->getEdges().size() == 0);

    QVERIFY(((Cluster*)mainCluster->getVertexes()[0])->getChildrenID().size()==2);
    //first cluster
    QVERIFY(((Cluster*)mainCluster->getVertexes()[0])->getChildrenID().contains(0));
    QVERIFY(((Cluster*)mainCluster->getVertexes()[0])->getChildrenID().contains(1));
    graphs.push_back(&graph);
    graphs.push_back(resultGraph);
    graphs.push_back(mainCluster);
}
/**
 * @brief UnitTestTest::layout
 * Layout methdod
 * Verfify if coordinates are good
 */
void UnitTestTest::layout()
{

    Layout layout(graphs);
    layout.run(5);

    QVERIFY(mainCluster->getVertexes()[0]->x==0);
    QVERIFY(mainCluster->getVertexes()[0]->y==0);

    QVERIFY(resultGraph->getVertexes()[0]->x==3);
    QVERIFY(resultGraph->getVertexes()[0]->y==0);
    QVERIFY(resultGraph->getVertexes()[1]->x==-3);
    QVERIFY(resultGraph->getVertexes()[1]->x==-3);
}


int Vertex::STATICID = -1;
int Cluster::STATICID = -1;
QTEST_APPLESS_MAIN(UnitTestTest)

#include "tst_unittesttest.moc"
