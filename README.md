# Sorting Fixed-Length IDs: MergeSort vs QuickSort

**Problem:** A social media application needs to sort fixed-length (3-digit) IDs.

**Input data:** `324, 125, 456, 218, 102, 389, 275, 147`

---

## Repository Structure

```
.
├── README.md              # This file
├── mergesort.c             # MergeSort source code
├── quicksort.c              # QuickSort source code
├── input.txt                # Input data
├── mergesort_output.txt     # Program output / trace (MergeSort)
├── quicksort_output.txt     # Program output / trace (QuickSort)
```

---

## a) MergeSort — Execution and Trace Table

MergeSort recursively splits the array into halves, sorts each half, then
**merges** them back together. The trace below records the array contents
after every merge (combine) operation, in the order they occur.

| Merge # | Range (l..r) | Mid | Subarray merged        | Full array after this merge          |
|:-------:|:------------:|:---:|-------------------------|----------------------------------------|
| 1 | 0..1 | 0 | 125 324 | 125 324 456 218 102 389 275 147 |
| 2 | 2..3 | 2 | 218 456 | 125 324 218 456 102 389 275 147 |
| 3 | 0..3 | 1 | 125 218 324 456 | 125 218 324 456 102 389 275 147 |
| 4 | 4..5 | 4 | 102 389 | 125 218 324 456 102 389 275 147 |
| 5 | 6..7 | 6 | 147 275 | 125 218 324 456 102 389 147 275 |
| 6 | 4..7 | 5 | 102 147 275 389 | 125 218 324 456 102 147 275 389 |
| 7 | 0..7 | 3 | 102 125 147 218 275 324 389 456 | 102 125 147 218 275 324 389 456 |

**Final sorted array:** `102 125 147 218 275 324 389 456`

**Metrics:** 17 comparisons, 7 merge operations (matches n−1 merge calls for n=8).

*(Note: the assignment sheet's phrase "after each digit position is processed"
matches Radix Sort terminology; since the question explicitly asks for
MergeSort, the trace instead records the array state after each merge step,
which is the equivalent intermediate checkpoint for this algorithm.)*

---

## b) QuickSort — Partition Trace Table

QuickSort (Lomuto partition scheme, pivot = last element of each subarray)
partitions the array around a pivot so smaller elements land on its left and
larger elements on its right, then recurses on both sides.

| Partition # | low | high | Pivot | Pivot's final index | Array after partition |
|:-----------:|:---:|:----:|:-----:|:--------------------:|-------------------------|
| 1 | 0 | 7 | 147 | 2 | 125 102 147 218 324 389 275 456 |
| 2 | 0 | 1 | 102 | 0 | 102 125 147 218 324 389 275 456 |
| 3 | 3 | 7 | 456 | 7 | 102 125 147 218 324 389 275 456 |
| 4 | 3 | 6 | 275 | 4 | 102 125 147 218 275 389 324 456 |
| 5 | 5 | 6 | 324 | 5 | 102 125 147 218 275 324 389 456 |

**Final sorted sequence:** `102 125 147 218 275 324 389 456`

**Metrics:** 16 comparisons, 5 partition operations.

---

## c) Comparison of MergeSort and QuickSort (n = 8)

| Criterion | MergeSort | QuickSort |
|---|---|---|
| Passes / recursive calls on this input | 7 merges | 5 partitions |
| Comparisons on this input | 17 | 16 |
| Best-case time complexity | O(n log n) | O(n log n) |
| Average-case time complexity | O(n log n) | O(n log n) |
| Worst-case time complexity | O(n log n) | O(n²) (already-sorted / bad-pivot input) |
| Space complexity | O(n) — needs auxiliary arrays for merging | O(log n) — in-place, only recursion stack |
| Stability | Stable | Not stable (Lomuto swap can reorder equal keys) |
| Behaviour on fixed-length numeric keys | Unaffected by key value distribution | Performance depends on pivot choice relative to key distribution |

---

## Time and Space Complexity — Justification

**MergeSort**
- Divides the array in half at every level → ⌈log₂ n⌉ levels of recursion.
- Each level does O(n) work to merge → total O(n log n) comparisons, guaranteed
  in every case (best, average, worst), because the split is always balanced
  regardless of input order.
- Requires O(n) extra space for the temporary `L[]`/`R[]` arrays used during merging.

**QuickSort**
- Average case: pivot splits the array roughly in half → O(n log n), same
  shape of recurrence as MergeSort, but with smaller constant factors since
  it sorts in place.
- Worst case: if the pivot (last element here) is always the smallest or
  largest of the remaining subarray — e.g. on already-sorted input — the
  split is maximally unbalanced (1 and n−1), giving O(n²).
- Space is O(log n) on average (recursion stack for a balanced split); it does
  not need auxiliary arrays because partitioning happens in place.

---

## Conclusion — Which is more appropriate for large fixed-length keys?

For sorting fixed-length numeric IDs (such as this 3-digit ID case) at
**large scale**:

- **QuickSort** is usually preferred in practice: it sorts in place (O(log n)
  space vs MergeSort's O(n)), has lower constant factors due to better cache
  locality, and its O(n²) worst case can be avoided almost entirely by using
  a randomized or median-of-three pivot — which is safe here because the IDs
  are simple fixed-length integers with no adversarial structure.
- **MergeSort** is the safer choice when a **guaranteed** O(n log n) bound is
  required regardless of input order (e.g. if IDs could arrive already
  sorted or reverse-sorted, which would degrade a naive QuickSort), or when
  **stability** matters (e.g. if IDs with equal values must preserve their
  original relative order, such as tie-breaking by timestamp).

**Overall recommendation:** for a social media application sorting large
volumes of fixed-length IDs where memory efficiency and average-case speed
matter and a good pivot strategy (randomized/median-of-three) is used,
**QuickSort** is the more appropriate choice. If worst-case guarantees or
stability are a hard requirement, **MergeSort** should be used instead.
