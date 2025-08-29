# Thank you ChatGPT for helping me make this script


#!/usr/bin/env bash
# run_benches_simple.sh — ExerciseFour -> notify -> ExerciseFive -> notify -> summary

WEBHOOK_URL="https://discord.com/api/webhooks/1411004588621824082/4awef-g2Ib31LJ1SrZuMpFNYlDYf9Jsb7Vdt2Sqn9agwBDvVo_C6NRu8t2ccy7MI4ewJ"

# Start
curl -H "Content-Type: application/json" \
     -X POST \
     -d '{"content": "Program started!"}' \
     "$WEBHOOK_URL"

start=$(date +%s)

# ---- ExerciseFour ----
gcc -O0 -mavx512f ../ExerciseFour.c -o ExerciseFour && ./ExerciseFour
rc_four=$?
elapsed_four=$(( $(date +%s) - start ))

curl -H "Content-Type: application/json" \
     -X POST \
     -d "{\"content\": \"ExerciseFour finished. Exit: $rc_four. Elapsed: ${elapsed_four}s.\"}" \
     "$WEBHOOK_URL"

# ---- ExerciseFive ----
gcc -O0 -mavx ../ExerciseFive.c -o ExerciseFive && ./ExerciseFive
rc_five=$?
elapsed_total=$(( $(date +%s) - start ))

curl -H "Content-Type: application/json" \
     -X POST \
     -d "{\"content\": \"ExerciseFive finished. Exit: $rc_five. Total elapsed: ${elapsed_total}s.\"}" \
     "$WEBHOOK_URL"

# ---- Final summary ----
msg="Summary on $(hostname)
Total elapsed: ${elapsed_total}s
ExerciseFour exit: ${rc_four}
ExerciseFive exit: ${rc_five}
When: $(date -Is)"

curl -H "Content-Type: application/json" \
     -X POST \
     -d "{\"content\": \"${msg}\"}" \
     "$WEBHOOK_URL"

# Exit nonzero if either failed
exit $(( rc_four || rc_five ))
