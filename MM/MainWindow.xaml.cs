using System;
using System.Collections.Generic;
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

namespace MM
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            homePage hp = new homePage();
            mainFrame.Content = hp;
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }

        private void ExitButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void MenuButton_Click(object sender, RoutedEventArgs e)
        {
            popMenu.IsOpen = true;
        }

        private void AboutButton_Click(object sender, RoutedEventArgs e)
        {
            popAbout.IsOpen = true;
        }

        private void SearchButton_Click(object sender, RoutedEventArgs e)
        {
            searchPage sp = new searchPage();
            mainFrame.Content = sp;
        }

        private void HomeButton_Click(object sender, RoutedEventArgs e)
        {
            homePage hp = new homePage();
            mainFrame.Content = hp;
        }
    }
}
