using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfApp2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            GetAllFilms();
            MoviesList.ItemsSource = Films;
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            DragMove();
        }

        // 获取所有影片文件名字
        private static void GetAllFilms(string path= "C:\\file\\films")
        {
            DirectoryInfo rootPath = new DirectoryInfo(path);
            FileSystemInfo[] filesArray = rootPath.GetFileSystemInfos();
            foreach (var item in filesArray)
            {
                if (item.Attributes == FileAttributes.Directory)
                {
                    GetAllFilms(item.FullName);
                }
                else
                {
                    MovieInfo movieInfo = new MovieInfo()
                    {
                        FileName = item.FullName
                    };
                    Films.Add(movieInfo);
                }
            }
        }

        // 所有影片文件列表
        private static List<MovieInfo> Films = new();

        private void addNewfilm_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("WIP.");
        }
    }

    class MovieInfo
    {
        public string? Name { get; set; }
        public string? FileName { get; set; }
    }
}
