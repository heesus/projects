/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package main;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
/**
 *
 * @author odani
 */
public class MainWindow extends  JFrame{

    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        spareLabel = new java.awt.Label();
        jInternalFrame1 = new javax.swing.JInternalFrame();
        jInternalFrame2 = new javax.swing.JInternalFrame();
        mainPanel = new javax.swing.JPanel();
        modeTab = new javax.swing.JTabbedPane();
        inputTab = new javax.swing.JPanel();
        inputScrollPane = new javax.swing.JScrollPane();
        inputTextArea = new javax.swing.JTextArea();
        openButton = new javax.swing.JButton();
        acceptButton = new javax.swing.JButton();
        displayTab = new javax.swing.JPanel();
        beginVisualizationButton = new javax.swing.JButton();
        stopButton = new javax.swing.JButton();
        prevStepButton = new javax.swing.JButton();
        nextStepButton = new javax.swing.JButton();
        continiousCheckBox = new javax.swing.JCheckBox();
        hintScrollPane = new javax.swing.JScrollPane();
        hintTextArea = new javax.swing.JTextArea();
        visualizationHintLabel = new java.awt.Label();
        resultTab = new javax.swing.JPanel();
        resultScrolPane = new javax.swing.JScrollPane();
        resultTextArea = new javax.swing.JTextArea();

        spareLabel.setText("label1");

        jInternalFrame1.setVisible(true);

        javax.swing.GroupLayout jInternalFrame1Layout = new javax.swing.GroupLayout(jInternalFrame1.getContentPane());
        jInternalFrame1.getContentPane().setLayout(jInternalFrame1Layout);
        jInternalFrame1Layout.setHorizontalGroup(
            jInternalFrame1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        jInternalFrame1Layout.setVerticalGroup(
            jInternalFrame1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        jInternalFrame2.setVisible(true);

        javax.swing.GroupLayout jInternalFrame2Layout = new javax.swing.GroupLayout(jInternalFrame2.getContentPane());
        jInternalFrame2.getContentPane().setLayout(jInternalFrame2Layout);
        jInternalFrame2Layout.setHorizontalGroup(
            jInternalFrame2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );
        jInternalFrame2Layout.setVerticalGroup(
            jInternalFrame2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 0, Short.MAX_VALUE)
        );

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        modeTab.setToolTipText("");
        modeTab.setCursor(new java.awt.Cursor(java.awt.Cursor.DEFAULT_CURSOR));
        modeTab.setName(""); // NOI18N

        inputTextArea.setColumns(20);
        inputTextArea.setRows(5);
        inputScrollPane.setViewportView(inputTextArea);

        openButton.setText("Открыть");
        openButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                openButtonActionPerformed(evt);
            }
        });

        acceptButton.setText("Применить");
        acceptButton.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                acceptButtonActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout inputTabLayout = new javax.swing.GroupLayout(inputTab);
        inputTab.setLayout(inputTabLayout);
        inputTabLayout.setHorizontalGroup(
            inputTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(inputTabLayout.createSequentialGroup()
                .addComponent(openButton, javax.swing.GroupLayout.PREFERRED_SIZE, 90, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(acceptButton)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
            .addComponent(inputScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 1033, Short.MAX_VALUE)
        );
        inputTabLayout.setVerticalGroup(
            inputTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, inputTabLayout.createSequentialGroup()
                .addGap(6, 6, 6)
                .addGroup(inputTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(openButton)
                    .addComponent(acceptButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(inputScrollPane, javax.swing.GroupLayout.DEFAULT_SIZE, 681, Short.MAX_VALUE))
        );

        modeTab.addTab("Ввод данных", inputTab);

        displayTab.setName(""); // NOI18N

        beginVisualizationButton.setText("Начать");
        beginVisualizationButton.setEnabled(false);

        stopButton.setText("Остановить");
        stopButton.setEnabled(false);

        prevStepButton.setText("Шаг назад");
        prevStepButton.setEnabled(false);

        nextStepButton.setText("Шаг вперед");
        nextStepButton.setEnabled(false);

        continiousCheckBox.setSelected(true);
        continiousCheckBox.setText("Выполнять непрерывно");

        hintTextArea.setColumns(20);
        hintTextArea.setRows(5);
        hintScrollPane.setViewportView(hintTextArea);

        visualizationHintLabel.setFont(new java.awt.Font("Dialog", 0, 14)); // NOI18N
        visualizationHintLabel.setText("Пояснения к визуализации");

        javax.swing.GroupLayout displayTabLayout = new javax.swing.GroupLayout(displayTab);
        displayTab.setLayout(displayTabLayout);
        displayTabLayout.setHorizontalGroup(
            displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(displayTabLayout.createSequentialGroup()
                .addGroup(displayTabLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(displayTabLayout.createSequentialGroup()
                        .addComponent(beginVisualizationButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(prevStepButton, javax.swing.GroupLayout.PREFERRED_SIZE, 100, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(stopButton)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(nextStepButton))
                    .addComponent(continiousCheckBox))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
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
                    .addComponent(nextStepButton))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(continiousCheckBox)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
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
            .addComponent(resultScrolPane, javax.swing.GroupLayout.DEFAULT_SIZE, 1033, Short.MAX_VALUE)
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

    private void openButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_openButtonActionPerformed
                JFileChooser fileChooser = new JFileChooser();
                FileNameExtensionFilter filter = new FileNameExtensionFilter("Text", "txt");
                fileChooser.setFileFilter(filter);
                int result = fileChooser.showOpenDialog(null);

                if(result == JFileChooser.APPROVE_OPTION){
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
                        while((line = reader.readLine()) != null)
                        {
                            content += line;
                            content += System.lineSeparator();
                        }
                    } catch (IOException e1) {
                        e1.printStackTrace();
                    }
                    inputTextArea.setText(content);
                }
    }//GEN-LAST:event_openButtonActionPerformed

    private void acceptButtonActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_acceptButtonActionPerformed
        String text = inputTextArea.getText();
        if (text.isEmpty()){
            JOptionPane.showMessageDialog(null, "Файл пустой!");
        }
        else {
            //???????
        }
    }//GEN-LAST:event_acceptButtonActionPerformed

    /**
     * @param args the command line arguments
     */

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton acceptButton;
    private javax.swing.JButton beginVisualizationButton;
    private javax.swing.JCheckBox continiousCheckBox;
    private javax.swing.JPanel displayTab;
    private javax.swing.JScrollPane hintScrollPane;
    private javax.swing.JTextArea hintTextArea;
    private javax.swing.JScrollPane inputScrollPane;
    private javax.swing.JPanel inputTab;
    private javax.swing.JTextArea inputTextArea;
    private javax.swing.JInternalFrame jInternalFrame1;
    private javax.swing.JInternalFrame jInternalFrame2;
    private javax.swing.JPanel mainPanel;
    private javax.swing.JTabbedPane modeTab;
    private javax.swing.JButton nextStepButton;
    private javax.swing.JButton openButton;
    private javax.swing.JButton prevStepButton;
    private javax.swing.JScrollPane resultScrolPane;
    private javax.swing.JPanel resultTab;
    private javax.swing.JTextArea resultTextArea;
    private java.awt.Label spareLabel;
    private javax.swing.JButton stopButton;
    private java.awt.Label visualizationHintLabel;
    // End of variables declaration//GEN-END:variables

public MainWindow() {
        initComponents();
        this.setVisible(true);
        this.setTitle("Наибольшее паросочетание в двудольном графе");

    }

}
