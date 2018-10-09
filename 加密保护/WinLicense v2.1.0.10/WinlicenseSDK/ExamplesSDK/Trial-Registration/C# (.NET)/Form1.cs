using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using System.Runtime.InteropServices;
using System.Text;
using System.IO;

namespace WindowsApplication1
{
    /// <summary>
    /// Summary description for Form1.
    /// </summary>
    public class Form1 : System.Windows.Forms.Form
    {
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button CheckStatusButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label StatusLabel;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label DaysLeftLabel;
        private System.Windows.Forms.Label ExecLeftLabel;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label MinutesLeftLabel;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label RuntimeLabel;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label RegDaysLeftLabel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label RegExecLeftLabel;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.DateTimePicker dateTimePicker2;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button HardIdButton;
        private System.Windows.Forms.TextBox HardIdEdit;
        private System.Windows.Forms.TextBox NameEdit;
        private System.Windows.Forms.TextBox CompanyEdit;
        private System.Windows.Forms.TextBox CustomEdit;
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.Container components = null;

        public Form1()
        {
            //
            // Required for Windows Form Designer support
            //
            InitializeComponent();

            //
            // TODO: Add any constructor code after InitializeComponent call
            //

            // We make the following call to allow testing in an unprotected state.
            // "LoadWinlicenseDll" will set up the environment variables with your custom valued in WinlicenseSDK.ini
            // NOTE: In your release version, before protecting, you have to REMOVE this call!!!
            
           // #if _DEBUG_MODE_
           //     WinlicenseSDK.WLLoadWinlicenseDll();
          //  #endif  

        }

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        protected override void Dispose( bool disposing )
        {
            if( disposing )
            {
                if (components != null) 
                {
                    components.Dispose();
                }
            }
            base.Dispose( disposing );
        }

		#region Windows Form Designer generated code
        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.StatusLabel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.CheckStatusButton = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.RuntimeLabel = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.MinutesLeftLabel = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.ExecLeftLabel = new System.Windows.Forms.Label();
            this.DaysLeftLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.dateTimePicker2 = new System.Windows.Forms.DateTimePicker();
            this.label13 = new System.Windows.Forms.Label();
            this.CustomEdit = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.RegExecLeftLabel = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.RegDaysLeftLabel = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.CompanyEdit = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.NameEdit = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.HardIdEdit = new System.Windows.Forms.TextBox();
            this.HardIdButton = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.StatusLabel,
                                                                                    this.label1,
                                                                                    this.CheckStatusButton});
            this.groupBox1.Location = new System.Drawing.Point(32, 24);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(368, 104);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Application Status";
            // 
            // StatusLabel
            // 
            this.StatusLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.StatusLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.StatusLabel.Location = new System.Drawing.Point(88, 65);
            this.StatusLabel.Name = "StatusLabel";
            this.StatusLabel.Size = new System.Drawing.Size(256, 23);
            this.StatusLabel.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(40, 72);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 23);
            this.label1.TabIndex = 1;
            this.label1.Text = "Status:";
            // 
            // CheckStatusButton
            // 
            this.CheckStatusButton.Location = new System.Drawing.Point(104, 24);
            this.CheckStatusButton.Name = "CheckStatusButton";
            this.CheckStatusButton.Size = new System.Drawing.Size(176, 23);
            this.CheckStatusButton.TabIndex = 0;
            this.CheckStatusButton.Text = "Check Application Status";
            this.CheckStatusButton.Click += new System.EventHandler(this.CheckStatusButton_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.dateTimePicker1,
                                                                                    this.RuntimeLabel,
                                                                                    this.label9,
                                                                                    this.MinutesLeftLabel,
                                                                                    this.label7,
                                                                                    this.ExecLeftLabel,
                                                                                    this.DaysLeftLabel,
                                                                                    this.label4,
                                                                                    this.label3,
                                                                                    this.label2});
            this.groupBox2.Location = new System.Drawing.Point(32, 152);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(368, 128);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Trial Information";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.Enabled = false;
            this.dateTimePicker1.Location = new System.Drawing.Point(104, 88);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.TabIndex = 9;
            // 
            // RuntimeLabel
            // 
            this.RuntimeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.RuntimeLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.RuntimeLabel.Location = new System.Drawing.Point(248, 54);
            this.RuntimeLabel.Name = "RuntimeLabel";
            this.RuntimeLabel.Size = new System.Drawing.Size(80, 23);
            this.RuntimeLabel.TabIndex = 8;
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(176, 57);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(72, 23);
            this.label9.TabIndex = 7;
            this.label9.Text = "Runtime Left:";
            // 
            // MinutesLeftLabel
            // 
            this.MinutesLeftLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.MinutesLeftLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.MinutesLeftLabel.Location = new System.Drawing.Point(248, 21);
            this.MinutesLeftLabel.Name = "MinutesLeftLabel";
            this.MinutesLeftLabel.Size = new System.Drawing.Size(80, 23);
            this.MinutesLeftLabel.TabIndex = 6;
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(176, 24);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(72, 23);
            this.label7.TabIndex = 5;
            this.label7.Text = "Minutes Left:";
            // 
            // ExecLeftLabel
            // 
            this.ExecLeftLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.ExecLeftLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.ExecLeftLabel.Location = new System.Drawing.Point(104, 56);
            this.ExecLeftLabel.Name = "ExecLeftLabel";
            this.ExecLeftLabel.Size = new System.Drawing.Size(64, 23);
            this.ExecLeftLabel.TabIndex = 4;
            // 
            // DaysLeftLabel
            // 
            this.DaysLeftLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.DaysLeftLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.DaysLeftLabel.Location = new System.Drawing.Point(104, 29);
            this.DaysLeftLabel.Name = "DaysLeftLabel";
            this.DaysLeftLabel.Size = new System.Drawing.Size(64, 23);
            this.DaysLeftLabel.TabIndex = 3;
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(16, 92);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(88, 24);
            this.label4.TabIndex = 2;
            this.label4.Text = "Expiration Date:";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(16, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(88, 16);
            this.label3.TabIndex = 1;
            this.label3.Text = "Executions Left:";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(43, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 16);
            this.label2.TabIndex = 0;
            this.label2.Text = "Days Left:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.dateTimePicker2,
                                                                                    this.label13,
                                                                                    this.CustomEdit,
                                                                                    this.label12,
                                                                                    this.RegExecLeftLabel,
                                                                                    this.label11,
                                                                                    this.RegDaysLeftLabel,
                                                                                    this.label10,
                                                                                    this.CompanyEdit,
                                                                                    this.label6,
                                                                                    this.NameEdit,
                                                                                    this.label5});
            this.groupBox3.Location = new System.Drawing.Point(32, 304);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(368, 144);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "License Information";
            // 
            // dateTimePicker2
            // 
            this.dateTimePicker2.Enabled = false;
            this.dateTimePicker2.Location = new System.Drawing.Point(109, 110);
            this.dateTimePicker2.Name = "dateTimePicker2";
            this.dateTimePicker2.TabIndex = 11;
            // 
            // label13
            // 
            this.label13.Location = new System.Drawing.Point(18, 112);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(88, 24);
            this.label13.TabIndex = 10;
            this.label13.Text = "Expiration Date:";
            // 
            // CustomEdit
            // 
            this.CustomEdit.Location = new System.Drawing.Point(256, 24);
            this.CustomEdit.Multiline = true;
            this.CustomEdit.Name = "CustomEdit";
            this.CustomEdit.Size = new System.Drawing.Size(96, 40);
            this.CustomEdit.TabIndex = 9;
            this.CustomEdit.Text = "";
            // 
            // label12
            // 
            this.label12.Location = new System.Drawing.Point(192, 24);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(48, 16);
            this.label12.TabIndex = 8;
            this.label12.Text = "Custom:";
            // 
            // RegExecLeftLabel
            // 
            this.RegExecLeftLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.RegExecLeftLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.RegExecLeftLabel.Location = new System.Drawing.Point(248, 82);
            this.RegExecLeftLabel.Name = "RegExecLeftLabel";
            this.RegExecLeftLabel.Size = new System.Drawing.Size(72, 23);
            this.RegExecLeftLabel.TabIndex = 7;
            // 
            // label11
            // 
            this.label11.Location = new System.Drawing.Point(160, 88);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(88, 16);
            this.label11.TabIndex = 6;
            this.label11.Text = "Executions Left:";
            // 
            // RegDaysLeftLabel
            // 
            this.RegDaysLeftLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((System.Byte)(0)));
            this.RegDaysLeftLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.RegDaysLeftLabel.Location = new System.Drawing.Point(80, 81);
            this.RegDaysLeftLabel.Name = "RegDaysLeftLabel";
            this.RegDaysLeftLabel.Size = new System.Drawing.Size(72, 23);
            this.RegDaysLeftLabel.TabIndex = 5;
            // 
            // label10
            // 
            this.label10.Location = new System.Drawing.Point(16, 88);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 16);
            this.label10.TabIndex = 4;
            this.label10.Text = "Days Left:";
            // 
            // CompanyEdit
            // 
            this.CompanyEdit.Location = new System.Drawing.Point(64, 48);
            this.CompanyEdit.Name = "CompanyEdit";
            this.CompanyEdit.TabIndex = 3;
            this.CompanyEdit.Text = "";
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(8, 52);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(56, 23);
            this.label6.TabIndex = 2;
            this.label6.Text = "Company:";
            // 
            // NameEdit
            // 
            this.NameEdit.Location = new System.Drawing.Point(64, 24);
            this.NameEdit.Name = "NameEdit";
            this.NameEdit.TabIndex = 1;
            this.NameEdit.Text = "";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(22, 27);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(40, 16);
            this.label5.TabIndex = 0;
            this.label5.Text = "Name:";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                                    this.HardIdEdit,
                                                                                    this.HardIdButton});
            this.groupBox4.Location = new System.Drawing.Point(32, 464);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(368, 88);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Hardware ID";
            // 
            // HardIdEdit
            // 
            this.HardIdEdit.Location = new System.Drawing.Point(160, 40);
            this.HardIdEdit.Name = "HardIdEdit";
            this.HardIdEdit.Size = new System.Drawing.Size(192, 20);
            this.HardIdEdit.TabIndex = 1;
            this.HardIdEdit.Text = "";
            // 
            // HardIdButton
            // 
            this.HardIdButton.Location = new System.Drawing.Point(24, 40);
            this.HardIdButton.Name = "HardIdButton";
            this.HardIdButton.Size = new System.Drawing.Size(112, 23);
            this.HardIdButton.TabIndex = 0;
            this.HardIdButton.Text = "Get Hardware ID";
            this.HardIdButton.Click += new System.EventHandler(this.HardIdButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(440, 573);
            this.Controls.AddRange(new System.Windows.Forms.Control[] {
                                                                          this.groupBox4,
                                                                          this.groupBox3,
                                                                          this.groupBox2,
                                                                          this.groupBox1});
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.ResumeLayout(false);

        }
		#endregion

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main() 
        {
            Application.Run(new Form1());
        }

        private void CheckStatusButton_Click(object sender, System.EventArgs e)
        {
            StringBuilder BufferVarValue = new StringBuilder(100);
            int TrialStatus;
			string [] LicenseInfo = null;

            Kernel32.GetEnvironmentVariable("WLRegGetStatus", BufferVarValue, 100);
        
            // show application status

            TrialStatus = System.Convert.ToInt32(BufferVarValue.ToString());

            switch (TrialStatus)
            {
                case 0:
                    this.StatusLabel.Text = "Trial";
                    break;

                case 1:
                    this.StatusLabel.Text = "Registered";
                    break;

                case 2:
                    this.StatusLabel.Text = "License key INVALID";
                    break;

                case 3:
                    this.StatusLabel.Text = "Wrong Hardware ID for current machine";
                    break;

                case 4:
                    this.StatusLabel.Text = "No more Hardware ID changes allowed";
                    break;

                case 5:
                    this.StatusLabel.Text = "License key expired";
                    break;
            }

            // print specific information for trial and registration
            
            if (TrialStatus != 1)
            {
                // application is not registered, show trial information

                Kernel32.GetEnvironmentVariable("WLTrialDaysLeft", BufferVarValue, 100);
                this.DaysLeftLabel.Text = BufferVarValue.ToString();

                Kernel32.GetEnvironmentVariable("WLTrialExecutionsLeft", BufferVarValue, 100);
                this.ExecLeftLabel.Text = BufferVarValue.ToString();

                Kernel32.GetEnvironmentVariable("WLTrialGlobalTimeLeft", BufferVarValue, 100);
                this.MinutesLeftLabel.Text = BufferVarValue.ToString();

                Kernel32.GetEnvironmentVariable("WLTrialRuntimeLeft", BufferVarValue, 100);
                this.RuntimeLabel.Text = BufferVarValue.ToString();

                Kernel32.GetEnvironmentVariable("WLTrialExpirationDate", BufferVarValue, 100);
                dateTimePicker1.Value = DateTime.Parse(BufferVarValue.ToString()); 

            }
            else
            {
                // application is registered, show registration data
            
                Kernel32.GetEnvironmentVariable("WLRegDaysLeft", BufferVarValue, 100);
                this.RegDaysLeftLabel.Text = BufferVarValue.ToString();
           
                Kernel32.GetEnvironmentVariable("WLRegExecutionsLeft", BufferVarValue, 100);
                this.RegExecLeftLabel.Text = BufferVarValue.ToString();
               
                Kernel32.GetEnvironmentVariable("WLRegGetLicenseInfo", BufferVarValue, 100);
				LicenseInfo = BufferVarValue.ToString().Split(',');

				this.NameEdit.Text = LicenseInfo[0];
                this.CompanyEdit.Text = LicenseInfo[1];
                this.CustomEdit.Text = LicenseInfo[2];

                Kernel32.GetEnvironmentVariable("WLRegExpirationDate", BufferVarValue, 100);
                dateTimePicker2.Value = DateTime.Parse(BufferVarValue.ToString()); 
            }
        }

        private void HardIdButton_Click(object sender, System.EventArgs e)
        {
            StringBuilder BufferVarValue = new StringBuilder(100);
            
            Kernel32.GetEnvironmentVariable("WLHardwareGetID", BufferVarValue, 100);
            this.HardIdEdit.Text = BufferVarValue.ToString();
        
        }
    }

    /****************************************************************************** 
    /* Class: Kernel32
    /*
    /* Description: Wrapper for Kernel32 Dll
    /*
    /******************************************************************************/

    class Kernel32
    {
        [DllImport( "Kernel32.dll", EntryPoint="GetEnvironmentVariable", CallingConvention = CallingConvention.StdCall )]
        public static extern int GetEnvironmentVariable(string lpName, StringBuilder lpBuffer, int nSize);

    }

    /****************************************************************************** 
    /* Class: WinlicenseSDK
    /*
    /* Description: Wrapper for the Winlicense SDK APIs
    /*
    /******************************************************************************/

    class WinlicenseSDK
    {
        [DllImport( "WinlicenseSDK.dll", EntryPoint="WLLoadWinlicenseDll", CallingConvention = CallingConvention.StdCall )]
        public static extern void WLLoadWinlicenseDll();
    }
}