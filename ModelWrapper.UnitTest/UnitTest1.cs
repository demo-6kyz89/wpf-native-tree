using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ViewModel;

namespace ModelWrapper.UnitTest
{
	[TestClass]
	public class UnitTest1
	{
		[TestMethod]
		public void WrapperCreate()
		{
			TreeNode node = CreateTestModel();
			Assert.IsNotNull( node );
		}

		[TestMethod]
		public void WrapperRemoveFirstChild()
		{
			TreeNode node = CreateTestModel();
			TreeNode firstChild = node.Children[0];
			node.RemoveChild( firstChild );
			Assert.IsNull( firstChild.Parent );
		}

		[TestMethod]
		public void WrapperSerialization()
		{
			string fileName = "wrapper.bin";
			TreeNode node = CreateTestModel();
			node.Save( fileName );
			TreeNode node1 = TreeNode.Open( fileName );
			Assert.IsTrue( node.Value == node1.Value );
			Assert.IsTrue( node.Children[0].Value == node1.Children[0].Value );
			Assert.IsTrue( node.Children[node.Children.Count - 1].Value == node1.Children[node1.Children.Count - 1].Value );
		}

		[TestMethod]
		public void ViewModelCreate()
		{
			TreeNode node = CreateTestModel();
			TreeNodeVM vm = new TreeNodeVM( node );
			Assert.IsNotNull( vm );
		}

		[TestMethod]
		public void ViewModelRemoveFirstChild()
		{
			TreeNode node = CreateTestModel();
			TreeNodeVM vm = new TreeNodeVM( node );
			TreeNodeVM firstChild = vm.Children[0];
			vm.Children.RemoveAt( 0 );
			Assert.IsNull( firstChild.Parent );
		}

		[TestMethod]
		public void ViewModelUpdateValue()
		{
			TreeNode node = CreateTestModel();
			TreeNodeVM vm = new TreeNodeVM( node );
			TreeNodeVM firstChild = vm.Children[0];
			firstChild.Value = 17;
			Assert.IsTrue( firstChild.Value == firstChild.Node.Value );
		}


		private TreeNode CreateTestModel()
		{
			TreeNode root = new TreeNode( 4 );

			TreeNode node1 = new TreeNode( 8 );
			root.AddChild( node1 );

			TreeNode node11 = new TreeNode( 7 );
			node1.AddChild( node11 );

			TreeNode node12 = new TreeNode( 1 );
			node1.AddChild( node12 );

			TreeNode node2 = new TreeNode( 2 );
			root.AddChild( node2 );

			TreeNode node21 = new TreeNode( 9 );
			node2.AddChild( node21 );

			return root;
		}
	}
}
