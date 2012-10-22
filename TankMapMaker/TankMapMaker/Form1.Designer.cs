namespace TankMapMaker
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.panelMap = new System.Windows.Forms.Panel();
            this.comboBoxCellTypes = new System.Windows.Forms.ComboBox();
            this.btnSelectCellType = new System.Windows.Forms.Button();
            this.lblMouseCoordinates = new System.Windows.Forms.Label();
            this.lblGridCoordinates = new System.Windows.Forms.Label();
            this.lblMapCoordinates = new System.Windows.Forms.Label();
            this.btnExport = new System.Windows.Forms.Button();
            this.btnFill = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // panelMap
            // 
            this.panelMap.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelMap.Location = new System.Drawing.Point(160, 12);
            this.panelMap.Name = "panelMap";
            this.panelMap.Size = new System.Drawing.Size(592, 487);
            this.panelMap.TabIndex = 0;
            this.panelMap.Paint += new System.Windows.Forms.PaintEventHandler(this.panelMap_Paint);
            this.panelMap.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panelMap_MouseDown);
            // 
            // comboBoxCellTypes
            // 
            this.comboBoxCellTypes.FormattingEnabled = true;
            this.comboBoxCellTypes.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9"});
            this.comboBoxCellTypes.Location = new System.Drawing.Point(1, 12);
            this.comboBoxCellTypes.Name = "comboBoxCellTypes";
            this.comboBoxCellTypes.Size = new System.Drawing.Size(153, 21);
            this.comboBoxCellTypes.TabIndex = 0;
            // 
            // btnSelectCellType
            // 
            this.btnSelectCellType.Location = new System.Drawing.Point(1, 39);
            this.btnSelectCellType.Name = "btnSelectCellType";
            this.btnSelectCellType.Size = new System.Drawing.Size(153, 23);
            this.btnSelectCellType.TabIndex = 0;
            this.btnSelectCellType.Text = "Select Type";
            this.btnSelectCellType.UseVisualStyleBackColor = true;
            this.btnSelectCellType.Click += new System.EventHandler(this.btnSelectCellType_Click);
            // 
            // lblMouseCoordinates
            // 
            this.lblMouseCoordinates.AutoSize = true;
            this.lblMouseCoordinates.Location = new System.Drawing.Point(-2, 442);
            this.lblMouseCoordinates.Name = "lblMouseCoordinates";
            this.lblMouseCoordinates.Size = new System.Drawing.Size(35, 13);
            this.lblMouseCoordinates.TabIndex = 0;
            this.lblMouseCoordinates.Text = "label1";
            // 
            // lblGridCoordinates
            // 
            this.lblGridCoordinates.AutoSize = true;
            this.lblGridCoordinates.Location = new System.Drawing.Point(-2, 464);
            this.lblGridCoordinates.Name = "lblGridCoordinates";
            this.lblGridCoordinates.Size = new System.Drawing.Size(35, 13);
            this.lblGridCoordinates.TabIndex = 1;
            this.lblGridCoordinates.Text = "label2";
            // 
            // lblMapCoordinates
            // 
            this.lblMapCoordinates.AutoSize = true;
            this.lblMapCoordinates.Location = new System.Drawing.Point(-2, 488);
            this.lblMapCoordinates.Name = "lblMapCoordinates";
            this.lblMapCoordinates.Size = new System.Drawing.Size(35, 13);
            this.lblMapCoordinates.TabIndex = 2;
            this.lblMapCoordinates.Text = "label3";
            // 
            // btnExport
            // 
            this.btnExport.Location = new System.Drawing.Point(1, 106);
            this.btnExport.Name = "btnExport";
            this.btnExport.Size = new System.Drawing.Size(153, 23);
            this.btnExport.TabIndex = 0;
            this.btnExport.Text = "Export";
            this.btnExport.UseVisualStyleBackColor = true;
            this.btnExport.Click += new System.EventHandler(this.btnExport_Click);
            // 
            // btnFill
            // 
            this.btnFill.Location = new System.Drawing.Point(1, 68);
            this.btnFill.Name = "btnFill";
            this.btnFill.Size = new System.Drawing.Size(153, 23);
            this.btnFill.TabIndex = 3;
            this.btnFill.Text = "Fill";
            this.btnFill.UseVisualStyleBackColor = true;
            this.btnFill.Click += new System.EventHandler(this.btnFill_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(755, 501);
            this.Controls.Add(this.btnFill);
            this.Controls.Add(this.btnExport);
            this.Controls.Add(this.lblMapCoordinates);
            this.Controls.Add(this.lblGridCoordinates);
            this.Controls.Add(this.lblMouseCoordinates);
            this.Controls.Add(this.btnSelectCellType);
            this.Controls.Add(this.comboBoxCellTypes);
            this.Controls.Add(this.panelMap);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.e);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panelMap;
        private System.Windows.Forms.ComboBox comboBoxCellTypes;
        private System.Windows.Forms.Button btnSelectCellType;
        private System.Windows.Forms.Label lblMouseCoordinates;
        private System.Windows.Forms.Label lblGridCoordinates;
        private System.Windows.Forms.Label lblMapCoordinates;
        private System.Windows.Forms.Button btnExport;
        private System.Windows.Forms.Button btnFill;
    }
}

