using ModelWrapper;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace ViewModel
{
	public class TreeNodeVM : DependencyObject
	{
		public TreeNodeVM(TreeNode node, TreeNodeVM parent = null)
		{
			Node = node;
			Value = node.Value;
			Parent = parent;
			Children = new ObservableCollection<TreeNodeVM>();
			foreach ( TreeNode child in node.Children )
				Children.Add( new TreeNodeVM( child, this ) );
			Children.CollectionChanged += Children_CollectionChanged;
		}

		public TreeNodeVM() : this( new TreeNode() ) { }


		public void Save(string fileName)
		{
			Node.Save( fileName );
		}

		public static TreeNodeVM Open(string fileName)
		{
			TreeNode node = TreeNode.Open( fileName );
			return new TreeNodeVM( node );
		}

		public void ExpandAll()
		{
			IsExpanded = true;
			foreach ( var item in Children )
				item.ExpandAll();
		}

		public void CollapseAll()
		{
			IsExpanded = false;
			foreach ( var item in Children )
				item.CollapseAll();
		}

		public string ToSubtreeString()
		{
			StringBuilder sb = new StringBuilder();
			ToSubtreeString( sb, 0 );
			return sb.ToString();
		}

		private void ToSubtreeString(StringBuilder sb, int indent)
		{
			for ( int i = 0; i < indent; i++ )
				sb.Append( "   " );
			sb.AppendLine( $"{Value}" );
			indent++;
			foreach ( var item in Children )
				item.ToSubtreeString( sb, indent );
			indent--;
		}


		private void Children_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
		{
			if ( e.OldItems != null )
			{
				foreach ( TreeNodeVM vm in e.OldItems )
				{
					vm.Parent = null;
					Node.RemoveChild( vm.Node );
				}
			}
			if ( e.NewItems != null )
			{
				IsExpanded = true;
				foreach ( TreeNodeVM vm in e.NewItems )
				{
					vm.Parent = this;
					Node.AddChild( vm.Node );
				}
			}
		}


		public TreeNode Node { get; private set; }

		public TreeNodeVM Parent { get; private set; }

		public ObservableCollection<TreeNodeVM> Children { get; private set; }

		public int Value
		{
			get { return (int) GetValue( ValueProperty ); }
			set { SetValue( ValueProperty, value ); }
		}

		public static readonly DependencyProperty ValueProperty =
			 DependencyProperty.Register( "Value", typeof( int ), typeof( TreeNodeVM ), new PropertyMetadata( 0, OnValueChanged ) );

		private static void OnValueChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
		{
			TreeNodeVM vm = d as TreeNodeVM;
			vm.Node.Value = (int) e.NewValue;
		}

		public bool IsExpanded
		{
			get { return (bool) GetValue( IsExpandedProperty ); }
			set { SetValue( IsExpandedProperty, value ); }
		}

		public static readonly DependencyProperty IsExpandedProperty =
			 DependencyProperty.Register( "IsExpanded", typeof( bool ), typeof( TreeNodeVM ), new PropertyMetadata( false ) );

		public bool IsSelected
		{
			get { return (bool) GetValue( IsSelectedProperty ); }
			set { SetValue( IsSelectedProperty, value ); }
		}

		public static readonly DependencyProperty IsSelectedProperty =
			 DependencyProperty.Register( "IsSelected", typeof( bool ), typeof( TreeNodeVM ), new PropertyMetadata( false ) );

	}
}
