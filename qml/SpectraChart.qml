import QtQuick 2.12
import QtCharts 2.3
import QtGraphicalEffects 1.12
import QtQuick.Controls.Material 2.12

ChartView {
    id: chart
    legend.visible: false
    property bool autoScale: false
    SplineSeries {
        id: spectrumSeries
        axisX: axisX
        axisY: axisY
        color: Material.color(Material.Indigo)
        width: 2
    }
    ValueAxis {
        id: axisX
        min: 410
        max: 410 + 35 * 18
        titleText: "Wavelength"
    }

    ValueAxis {
        id: axisY
        readonly property int maxYValue: 2**16
        min: 0
        max: autoScale ? spectraProvider.yMax * 1.1 : maxYValue
        titleText: "Intensity"
    }

    Item {
        x: chart.plotArea.x
        y: chart.plotArea.y + chart.plotArea.height - height
        width: chart.plotArea.width / 2
        height: 6

        LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(width, 0)
            gradient: Gradient {
                GradientStop { position: 8/8; color: Qt.hsla(0, 1, 0.5, 1) }
                GradientStop { position: 7/8; color: Qt.hsla(0.1, 1, 0.5, 1) }
                GradientStop { position: 6/8; color: Qt.hsla(0.2, 1, 0.5, 1) }
                GradientStop { position: 5/8; color: Qt.hsla(0.3, 1, 0.5, 1) }
                GradientStop { position: 4/8; color: Qt.hsla(0.4, 1, 0.5, 1) }
                GradientStop { position: 3/8; color: Qt.hsla(0.5, 1, 0.5, 1) }
                GradientStop { position: 2/8; color: Qt.hsla(0.6, 1, 0.5, 1) }
                GradientStop { position: 1/8; color: Qt.hsla(0.7, 1, 0.5, 1) }
                GradientStop { position: 0/8; color: Qt.hsla(0.8, 1, 0.5, 1) }
            }
        }
    }
    Connections {
        target: spectraProvider
        onDataChanged: {
            console.log("data changed")
            spectraProvider.updateSeries(spectrumSeries)
        }
    }
}
