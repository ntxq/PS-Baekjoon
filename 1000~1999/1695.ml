open! StdLabels
open! MoreLabels

(*
   Subproblem: N[i, j] = # of insertions needed to make s[i..j] palindrome
   Recurrence: N[i, j] = if s[i] = s[j] then N[i+1, j-1] else 1 + min(N[i+1, j], N[i, j-1])
   Topological order: i from n-1 to 0, j from i to n-1
   Base case: N[i, j] = 0 if i >= j
   Original problem: N[0, n-1]
   Time complexity: O(n^2)
*)

let panlidrome_dist seq =
  let prev = Array.make (Array.length seq) 0 in
  let curr = Array.make (Array.length seq) 0 in

  for i = Array.length seq - 1 downto 0 do
    for j = i + 1 to Array.length seq - 1 do
      if Int.equal seq.(i) seq.(j) then curr.(j) <- prev.(j - 1)
      else curr.(j) <- 1 + min prev.(j) curr.(j - 1)
    done;
    Array.blit ~src:curr ~dst:prev ~src_pos:0 ~dst_pos:0 ~len:(Array.length seq)
  done;

  curr.(Array.length seq - 1)

let () =
  let _ = input_line stdin in
  let seq =
    input_line stdin
    |> String.split_on_char ~sep:' '
    |> List.map ~f:int_of_string |> Array.of_list
  in
  panlidrome_dist seq |> string_of_int |> print_endline
