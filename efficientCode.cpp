class Solution {
    public List<List<Integer>> findDifference(int[] nums1, int[] nums2) {
        Set<Integer> set1 = new HashSet<>();
        Set<Integer> set2 = new HashSet<>();
        
        for (int n : nums1) set1.add(n);
        for (int n : nums2) set2.add(n);
        
        // copy for difference calculation
        Set<Integer> only1 = new HashSet<>(set1);
        Set<Integer> only2 = new HashSet<>(set2);
        
        only1.removeAll(set2); // elements only in nums1
        only2.removeAll(set1); // elements only in nums2
        
        List<List<Integer>> ans = new ArrayList<>();
        ans.add(new ArrayList<>(only1));
        ans.add(new ArrayList<>(only2));
        return ans;
    }
}
