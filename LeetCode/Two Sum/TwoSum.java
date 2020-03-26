class Solution {
    public int[] twoSum(int[] nums, int target) {
        int[] res = new int[2];
        Map<Integer, Integer> rep = new HashMap<Integer, Integer>();
        for(int i = 0; i < nums.length; i++)
            rep.put(nums[i], i);
        for (int i = 0; i < nums.length; i++)
        {
            int num = target - nums[i];
            if(rep.containsKey(num) && rep.get(num) != i)
            {
                res[0] = i;
                res[1] = rep.get(num);
                break;
            }
        }
        return res;
    }
}