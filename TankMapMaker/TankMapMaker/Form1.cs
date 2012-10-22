using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace TankMapMaker
{
    public partial class Form1 : Form
    {
        const int width = 8;
        const int height = 8;

        int[,] mapData = new int[width, height];

        MapBrush current = null;
        MapBrush zero = new MapBrush("0.png",0);
        MapBrush one = new MapBrush("1.png",1);
        MapBrush two = new MapBrush("2.png",2);
        MapBrush three = new MapBrush("3.png",3);
        Bitmap map = new Bitmap(width * 16, height * 16);

        public Form1()
        {
            InitializeComponent();
        }

        void ConvertScreenToWorld(int sx, int sy, ref int wx, ref int wy)
        {
            wx = sx / width;
            wy = sy / height;
        }

        private void panelMap_MouseDown(object sender, MouseEventArgs e)
        {
            //int wx = 0;
            //int wy = 0;
            //ConvertScreenToWorld(e.Location.X, e.Location.Y, ref wx, ref wy);
            //txtX.Text = wx.ToString();
            //txtY.Text = wy.ToString();
            //mapData[wx, wy] = 'a';

            if (e.Button == System.Windows.Forms.MouseButtons.Left)
            {
                decimal bitmapDimX = 16;
                decimal bitmapDimY = 16;

                //Convert Mouse to Grid
                int gridCoordX = (int)Math.Floor((decimal)(e.X) / bitmapDimX) * (int)bitmapDimX;
                int gridCoordY = (int)Math.Floor((decimal)(e.Y) / bitmapDimY) * (int)bitmapDimY;

                //Convert Grid to Map
                int mapCoordX = gridCoordX / (int)bitmapDimX;
                int mapCoordY = gridCoordY / (int)bitmapDimY;

                //Print out Coordinate Info
                lblMouseCoordinates.Text = String.Format("Mouse: {0},{1}", e.X, e.Y);
                lblGridCoordinates.Text = String.Format("Grid : {0},{1}", gridCoordX, gridCoordY);
                lblMapCoordinates.Text = String.Format("Map   : {0},{1}", mapCoordX, mapCoordY);

                //Check for out of bounds
                if (mapCoordX >= 0 && mapCoordX < width)
                {
                    if (mapCoordY >= 0 && mapCoordY < height)
                    {
                        //Store Location in World map
                        //currentLocation.x = mapCoordX;
                        //currentLocation.y = mapCoordY;
                        //world.map[currentLocation.x, currentLocation.y] = currentLocation;
                        mapData[mapCoordX, mapCoordY] = current.code;

                        Graphics g = Graphics.FromImage(map);

                        g.DrawImage(current.bitmap, gridCoordX, gridCoordY, (float)bitmapDimX, (float)bitmapDimY);
                        g.Dispose();
                        panelMap.Refresh();
                    }
                }
            }
        }

        private void e(object sender, EventArgs e)
        {

        }

        private void panelMap_Paint(object sender, PaintEventArgs e)
        {
            
            e.Graphics.DrawImage(map, 0,0);
        }

        private void btnSelectCellType_Click(object sender, EventArgs e)
        {
            if (comboBoxCellTypes.SelectedIndex != -1)
            {
                int a = comboBoxCellTypes.SelectedIndex;
                if (a == 0)
                    current = zero;
                else if (a == 1)
                    current = one;
                else if (a == 2)
                    current = two;
                else if (a == 3)
                    current = three;
            }
        }

        private void btnFill_Click(object sender, EventArgs e)
        {
            if (comboBoxCellTypes.SelectedIndex != -1)
            {
                int a = comboBoxCellTypes.SelectedIndex;
                if (a == 0)
                    current = zero;
                else if (a == 1)
                    current = one;
                else if (a == 2)
                    current = two;
                else if (a == 3)
                    current = three;
                else
                    current = zero;
            }
            else
                current = zero;
            
            Graphics g = Graphics.FromImage(map);
            
            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    mapData[x, y] = current.code;
                    g.DrawImage(current.bitmap, x*16, y*16, (float)16, (float)16);
                }
            }


        }

        private void btnExport_Click(object sender, EventArgs e)
        {
            System.IO.StreamWriter sw = new System.IO.StreamWriter("export.txt");
            sw.WriteLine(width);//columns
            sw.WriteLine(height);//rows
            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    sw.Write(String.Format("{0}, ",mapData[x,y]));
                }
                sw.WriteLine();
            }
            sw.Close();
        }
    }
}
