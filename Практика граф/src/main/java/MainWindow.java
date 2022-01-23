/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.awt.Color;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

/**
 *
 * @author odani
 */
public class MainWindow extends JFrame {

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        inputDataDialog = new javax.swing.JDialog();
        jPanel2 = new javax.swing.JPanel();
        openButton = new javax.swing.JButton();
        aceeptButton = new javax.swing.JButton();
        jScrollPane2 = new javax.swing.JScrollPane();
        inputTextArea = new javax.swing.JTextArea();
        mainPanel = new javax.swing.JPanel();
        modeTab = new javax.swing.JTabbedPane();
        displayTab = new javax.swing.JPanel();
        beginVisualizationButton = new javax.swing.JButton();
        stopButton = new javax.swing.JButton();
        prevStepButton = new javax.swing.JButton();
        nextStepButton = new javax.swing.JButton();
        continiousCheckBox = new javax.swing.JCheckBox();
        hintScrollPane = new javax.swing.JScrollPane();
        hintTextArea = new javax.swing.JTextArea();
        visualizationHintLabel = new java.awt.Label();
        jPanel1 = new javax.swing.JPanel();
        inputDataButton = new javax.swing.JButton();
        completeAutomaticallyButton = new javax.swing.JButton();
        resultTab = new javax.swing.JPanel();
        resultScrolPane = new javax.swing.JScrollPane();
        resultTextArea = new javax.swing.JTextArea();

        inputDataDialog.setLocation(new java.awt.Point(200, 200));
        inputDataDialog.setSize(new java.awt.Dimension(400, 400));

        openButton.setText("Открыть");
        openButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openButtonActionPerformed(evt);
            }
        });

        aceeptButton.setText("Применить");
        aceeptButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                aceeptButtonActionPerformed(evt);
            }
        });

        inputTextArea.setColumns(20);
        inputTextArea.setRows(5);
        jScrollPane2.setViewportView(inputTextArea);

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addComponent(jScrollPane2)
                        .addContainerGap())
                    .addGroup(jPanel2Layout.createSequentialGroup()
                        .addGap(0, 73, Short.MAX_VALUE)
                        .addComponent(openButton)
                        .addGap(69, 69, 69)
                        .addComponent(aceeptButton)
                        .addGap(78, 78, 78))))
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addGap(19, 19, 19)
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(openButton)
                    .addComponent(aceeptButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.DEFAULT_SIZE, 253, Short.MAX_VALUE)
                .addContainerGap())
        );

        javax.swing.GroupLayout inputDataDialogLayout = new javax.swing.GroupLayout(inputDataDialog.getContentPane());
        inputDataDialog.getContentPane().setLayout(inputDataDialogLayout);
        inputDataDialogLayout.setHorizontalGroup(
            inputDataDialogLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        inputDataDialogLayout.setVerticalGroup(
            inputDataDialogLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        modeTab.setToolTipText("");
        modeTab.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        modeTab.setName(""); // NOI18N

        displayTab.setName(""); // NOI18N

        beginVisualizationButton.setText("Начать");
        beginVisualizationButton.setEnabled(false);
        beginVisualizationButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                beginVisualizationButtonActionPerformed(evt);
            }
        });

        stopButton.setText("Закончить");
        stopButton.setEnabled(false);
        stopButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                stopButtonActionPerformed(evt);
            }
        });

        prevStepButton.setText("Шаг назад");
        prevStepButton.setEnabled(false);
        prevStepButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                prevStepButtonActionPerformed(evt);
            }
        });

        nextStepButton.setText("Шаг вперед");
        nextStepButton.setEnabled(false);
        nextStepButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                nextStepButtonActionPerformed(evt);
            }
        });

        continiousCheckBox.setSelected(true);
        continiousCheckBox.setText("Выполнять непрерывно");
        continiousCheckBox.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                continiousCheckBoxActionPerformed(evt);
            }
        });

        hintTextArea.setColumns(20);
        hintTextArea.setRows(5);
        hintScrollPane.setViewportView(hintTextArea);

        visualizationHintLabel.setFont(new java.awt.Font("Dialog", 0, 14)); // NOI18N
        visualizationHintLabel.setText("Пояснения к визуализации");

        jPanel1.setBackground(new java.awt.Color(255, 255, 255));

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 650, Short.MAX_VALUE)
        );

        inputDataButton.setText("Ввести данные");
        inputDataButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                inputDataButtonActionPerformed(evt);
            }
        });

        completeAutomaticallyButton.setText("Завершить автоматически");
        completeAutomaticallyButton.setEnabled(false);
        completeAutomaticallyButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                completeAutomaticallyButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout displayTabLayout = new javax.swing.GroupLayout(displayTab);
        displayTab.setLayout(displayTabLayout);
        displayTabLayout.setHorizontalGroup(
            displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(displayTabLayout.createSequentialGroup()
                .addGroup(displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(displayTabLayout.createSequentialGroup()
                        .addGroup(displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(continiousCheckBox)
                            .addGroup(displayTabLayout.createSequentialGroup()
                                .addComponent(inputDataButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(beginVisualizationButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(prevStepButton, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(stopButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(nextStepButton)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(completeAutomaticallyButton)))
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(visualizationHintLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(hintScrollPane, javax.swing.GroupLayout.PREFERRED_SIZE, 404, javax.swing.GroupLayout.PREFERRED_SIZE)))
        );
        displayTabLayout.setVerticalGroup(
            displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(displayTabLayout.createSequentialGroup()
                .addContainerGap()
                .addGroup(displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(beginVisualizationButton)
                    .addComponent(stopButton)
                    .addComponent(prevStepButton)
                    .addComponent(nextStepButton)
                    .addComponent(inputDataButton)
                    .addComponent(completeAutomaticallyButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(continiousCheckBox)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, displayTabLayout.createSequentialGroup()
                .addComponent(visualizationHintLabel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(hintScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 683, Short.MAX_VALUE))
        );

        modeTab.addTab("Визуализация", null, displayTab, "");

        resultTextArea.setColumns(20);
        resultTextArea.setRows(5);
        resultScrolPane.setViewportView(resultTextArea);

        javax.swing.GroupLayout resultTabLayout = new javax.swing.GroupLayout(resultTab);
        resultTab.setLayout(resultTabLayout);
        resultTabLayout.setHorizontalGroup(
            resultTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(resultScrolPane, javax.swing.GroupLayout.DEFAULT_SIZE, 1081, Short.MAX_VALUE)
        );
        resultTabLayout.setVerticalGroup(
            resultTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, resultTabLayout.createSequentialGroup()
                .addComponent(resultScrolPane, javax.swing.GroupLayout.DEFAULT_SIZE, 705, Short.MAX_VALUE)
                .addContainerGap())
        );

        modeTab.addTab("Результат", resultTab);

        javax.swing.GroupLayout mainPanelLayout = new javax.swing.GroupLayout(mainPanel);
        mainPanel.setLayout(mainPanelLayout);
        mainPanelLayout.setHorizontalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(modeTab)
        );
        mainPanelLayout.setVerticalGroup(
            mainPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(modeTab)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(mainPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(mainPanel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void continiousCheckBoxActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_continiousCheckBoxActionPerformed
        if (continiousCheckBox.isSelected()) {
            nextStepButton.setEnabled(false);
            prevStepButton.setEnabled(false);
        }
    }//GEN-LAST:event_continiousCheckBoxActionPerformed

    private void nextStepButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_nextStepButtonActionPerformed
        getNextStep();
    }//GEN-LAST:event_nextStepButtonActionPerformed

    private void prevStepButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_prevStepButtonActionPerformed
        getPrevStep();
    }//GEN-LAST:event_prevStepButtonActionPerformed

    private void stopButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_stopButtonActionPerformed
        continiousCheckBox.setEnabled(true);
        beginVisualizationButton.setEnabled(true);
        completeAutomaticallyButton.setEnabled(false);
        stopButton.setEnabled(false);
        nextStepButton.setEnabled(false);
        prevStepButton.setEnabled(false);
        visual.stopped = true;
        visual.stepIndex = visual.getStepsCount();
        hintTextArea.setText(visual.getNextHint());
        repaint();
        timer.stop();
    }//GEN-LAST:event_stopButtonActionPerformed


    private void beginVisualizationButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_beginVisualizationButtonActionPerformed
        boolean continuousRunning = continiousCheckBox.isSelected();
        hintTextArea.setText("");
        visual.stepIndex = 0;
        repaint();
        visual.stepIndex = -1;

        continiousCheckBox.setEnabled(false);
        beginVisualizationButton.setEnabled(false);
        stopButton.setEnabled(true);
        if (!continuousRunning) {
            nextStepButton.setEnabled(true);
            prevStepButton.setEnabled(true);
            completeAutomaticallyButton.setEnabled(true);
        }

        if (continuousRunning) {
            startVisualization();
        }

        resultTextArea.setText(visual.getResult());
    }//GEN-LAST:event_beginVisualizationButtonActionPerformed

    private void inputDataButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_inputDataButtonActionPerformed
        inputDataDialog.setTitle("Введите данные");
        inputDataDialog.setVisible(true);
    }//GEN-LAST:event_inputDataButtonActionPerformed

    private void openButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openButtonActionPerformed
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Text", "txt");
        fileChooser.setFileFilter(filter);
        int result = fileChooser.showOpenDialog(null);

        if (result == JFileChooser.APPROVE_OPTION) {
            String name = fileChooser.getSelectedFile().getName();
            String absolutePath = fileChooser.getSelectedFile().getAbsolutePath();

            File file = new File(absolutePath);
            BufferedReader reader = null;
            try {
                reader = new BufferedReader(new FileReader(file));
            } catch (FileNotFoundException e1) {
                e1.printStackTrace();
            }
            String content = "";
            String line;
            try {
                while ((line = reader.readLine()) != null) {
                    content += line;
                    content += System.lineSeparator();
                }
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            inputTextArea.setText(content);
        }
    }//GEN-LAST:event_openButtonActionPerformed

    private void aceeptButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_aceeptButtonActionPerformed
        String text = inputTextArea.getText();
        if (text.isEmpty()) {
            JOptionPane.showMessageDialog(null, "Файл пустой!");
        } else {
            acceptGraph();
            startAlgorithm();
            hintTextArea.setText("");
        }
        inputDataDialog.setVisible(false);
    }//GEN-LAST:event_aceeptButtonActionPerformed

    private void completeAutomaticallyButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_completeAutomaticallyButtonActionPerformed
        stopButton.setEnabled(true);
        completeAutomaticallyButton.setEnabled(false);
        nextStepButton.setEnabled(false);
        prevStepButton.setEnabled(false);
        startVisualization();
    }//GEN-LAST:event_completeAutomaticallyButtonActionPerformed

    /**
     * @param args the command line arguments
     */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton aceeptButton;
    private javax.swing.JButton beginVisualizationButton;
    private javax.swing.JButton completeAutomaticallyButton;
    private javax.swing.JCheckBox continiousCheckBox;
    private javax.swing.JPanel displayTab;
    private javax.swing.JScrollPane hintScrollPane;
    private javax.swing.JTextArea hintTextArea;
    private javax.swing.JButton inputDataButton;
    private javax.swing.JDialog inputDataDialog;
    private javax.swing.JTextArea inputTextArea;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JTabbedPane modeTab;
    private javax.swing.JButton nextStepButton;
    private javax.swing.JButton openButton;
    private javax.swing.JButton prevStepButton;
    private javax.swing.JScrollPane resultScrolPane;
    private javax.swing.JPanel resultTab;
    private javax.swing.JTextArea resultTextArea;
    private javax.swing.JButton stopButton;
    private java.awt.Label visualizationHintLabel;
    // End of variables declaration//GEN-END:variables
    private Visualizer visual;
    ActionListener taskPerformer = new ActionListener() {
        public void actionPerformed(ActionEvent evt) {
            getNextStep();
            repaint();
        }
    };
    Timer timer = new Timer(500, taskPerformer);

    public MainWindow() {
        initComponents();
        visual = new Visualizer();

        visual.setBackground(new Color(255, 255, 255));

        GroupLayout displayTabLayout = (GroupLayout) displayTab.getLayout();

        displayTabLayout.replace(jPanel1, visual);

        this.setVisible(true);
        this.setTitle("Наибольшее паросочетание в двудольном графе");

    }

    private Graph readGraph(Graph g) {
        String str = inputTextArea.getText();
        String lines[] = str.split("\\r?\\n");
        for (String line : lines) {
            String elements[] = line.split("\\s+");
            if (elements.length == 2) {
                g.addEdge(elements[0], elements[1]);
            } else {
                throw new IllegalArgumentException("Неверный формат ввода");
            }
        }
        return g;
    }

    private void acceptGraph() {
        try {
            Graph g = new Graph();
            readGraph(g);
            BipartiteGraph result = new BipartiteGraph(g);
            visual.stepIndex = 0;
            visual.setGraph(result);
            beginVisualizationButton.setEnabled(true);
        } catch (IllegalArgumentException e) {
            JOptionPane.showMessageDialog(null, e.getMessage());
        }

    }

    public void startAlgorithm() {
        // очищаем результаты предыдущей работы алгоритма
        visual.setActiveEdge(null, null);
        visual.setCurrentMatching(null);

        visual.start();

    }

    public void startVisualization() {
        hintTextArea.setText("");

        int j = getStepsCounter();
        int i = 0;

        while (i != j) {
            timer.start();
            i++;
        }
    }

    public int getStepsCounter() {
        return visual.getStepsCount();
    }

    public void getNextStep() {
        hintTextArea.setText(visual.getNextHint());
        repaint();
    }

    public void getPrevStep() {
        hintTextArea.setText(visual.getPrevHint());
        repaint();
    }

}
